/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:00:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/03 12:51:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* @brief Extracts the name of a variable from a string.
*
* Gets the name of the variable after the `$` symbol at the given position,
* removing any spaces or unwanted characters.
*
* @param str String containing the variable.
* @param i Pointer to the current index in the string `str`.
* @return Variable name stripped of spaces and special characters.
*/
static char *get_variable_name(char *str, int *i)
{
	char *tmp;
	char *needle;

	tmp = dictionary(str, (*i) + 1);
	needle = ft_strtrim(tmp, " \n\t\r\v");
	free(tmp);
	return (needle);
}

/**
* @brief Expands the value of an environment variable into a string.
*
* Creates a new string with the existing prefix and the value of the variable
* obtained from the `envp` environment. If the variable is `$`, adds a special value
* (e.g., PID).
*
* @param str Original string containing the variable.
* @param i Pointer to the current index in the `str` string.
* @param envp Array of strings representing the environment variables.
* @param needle Name of the variable to expand.
* @return New string containing the expanded variable.
*/
static char *expand_variable(char *str, int *i, char **envp, char *needle)
{
	char *expanded;
	char *prefix;

	prefix = ft_substr(str, 0, (size_t)(*i));
	if (!ft_strncmp(needle, "$", 2))
		expanded = ft_strjoin(prefix, "no PID");
	else
		expanded = ft_strjoin(prefix, get_value_from_env(envp, needle, NULL));
	free(prefix);
	return (expanded);
}

/**
* @brief Concatenates the expanded string with the rest of the original.
*
* Joins the already expanded string with the contents after the variable name,
* thus creating a new complete string with the expanded value.
*
* @param expanded String containing the expanded part.
* @param str Original string.
* @param i Pointer to the current index in the string `str`.
* @param needle Name of the expanded variable.
* @return Final string with the complete expansion.
*/
static char *concat_expanded_string(char *expanded, char *str, int *i, char *needle)
{
	char *extract;

	extract = ft_substr(str, (*i) + 1 + ft_strlen(needle), SIZE_T_MAX);
	expanded = ft_strjoin(expanded, extract);
	free(extract);
	return (expanded);
}

/**
* @brief Expands an environment variable into a given string.
*
* Finds the variable name in `str`, expands it using `envp`, and
* replaces the variable in the original string with its corresponding value.
*
* @param str Original string with the variable to expand.
* @param i Pointer to the current index in the string `str`.
* @param envp Array of strings representing the environment variables.
* @return New string with the expanded variable.
*/
static char *expand_str(char *str, int *i, char **envp)
{
	char *needle;
	char *expanded;

	needle = get_variable_name(str, i);
	if (!*needle)
	{
		free(needle);
		(*i)++;
		return (str);
	}
	expanded = expand_variable(str, i, envp, needle);
	free(needle);
	expanded = concat_expanded_string(expanded, str, i, needle);
	free(str);
	return (expanded);
}

/**
* @brief Expands environment variables on a given line.
*
* Walks along `line`, expanding environment variables delimited by `$`.
* If the variable is inside single quotes, it is ignored unless `expand_all`
* is true. Expansions in double quotes are always allowed.
*
* @param line Original input line.
* @param envp Array of strings representing environment variables.
* @param expand_all Flag to expand variables inside single quotes.
* @return Expanded line with all environment variables resolved.
*/
char *ft_expand(char *line, char **envp, char expand_all)
{
	int i;
	char in_quotes;
	char *expanded;

	i = 0;
	in_quotes = 0;
	expanded = ft_strdup(line);
	while (expanded[i])
	{
		if (expanded[i] == '\"')
			in_quotes = !in_quotes;
		if (expanded[i] == '\'' && !in_quotes && !expand_all)
			skip_to_delimiter(expanded, &i, '\'');
		if (expanded[i] == '$')
			expanded = expand_str(expanded, &i, envp);
		else
			++i;
		if (!expanded)
			break ;
	}
	return (expanded);
}

