/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:34:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:39:10 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Expands a given string by replacing env variables with
		their values.
 *
 * This function takes a string and an index,
	and replaces any env variables
 * found in the string with their corresponding values from the
		provided env
 * variables array.
 *
 * @param str The input string to be expanded.
 * @param i Pointer to the current index in the string.
 * @param envp Array of env variables.
 * @return The expanded string with env variables replaced.
 */
static char	*expand_str_check(char *str, int *i, char **envp)
{
	char	*needle;
	char	*expanded;
	char	*extract;
	char	*tmp;

	tmp = dictionary(str, (*i) + 1);
	needle = ft_strtrim(tmp, " \n\t\r\v");
	free(tmp);
	if (!ft_strncmp(needle, "", 1))
		return (free(needle), ++(*i), str);
	expanded = ft_substr(str, 0, (size_t)(*i));
	tmp = expanded;
	if (!ft_strncmp(needle, "$", 2))
		expanded = ft_strjoin(tmp, "no PID, sorry :C");
	else
		expanded = ft_strjoin(tmp, ft_get_from_env(envp, needle, NULL));
	free(tmp);
	tmp = expanded;
	extract = ft_substr(str, (*i) + 1 + ft_strlen(needle), SIZE_T_MAX);
	expanded = ft_strjoin(expanded, extract);
	free(tmp);
	free(extract);
	free(needle);
	free(str);
	return (expanded);
}

/**
 * @brief Expands env variables in a given line.
 *
 * This function processes a line of text and expands any env variables
 * found in the line using the provided env variables array.
 * It also handles quoted strings and selectively expands variables
		based on the expand_all flag.
 *
 * @param line The input line to be expanded.
 * @param envp Array of env variables.
 * @param expand_all Flag indicating whether to expand all variables or not.
 * @return The expanded line with env variables replaced.
 */
char	*ft_expand_str(char *line, char **envp, char expand_all)
{
	int		i;
	char	in_quotes;
	char	*expanded;

	i = 0;
	expanded = ft_strdup(line);
	in_quotes = 0;
	while (expanded[i])
	{
		if (expanded[i] == '\"')
			in_quotes = !in_quotes;
		if (expanded[i] == '\'' && !in_quotes && !expand_all)
			state_quote_delimiter(expanded, &i, '\'');
		if (expanded[i] == '$')
			expanded = expand_str_check(expanded, &i, envp);
		else if (expanded[i])
			++i;
		if (!expanded)
			break ;
	}
	return (expanded);
}
