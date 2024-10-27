/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:00:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_variable_name(char *str, int *i)
{
	char	*tmp;
	char	*needle;

	tmp = dictionary(str, (*i) + 1);
	needle = ft_strtrim(tmp, " \n\t\r\v");
	free(tmp);
	return (needle);
}

static char	*expand_variable(char *str, int *i, char **envp, char *needle)
{
	char	*expanded;
	char	*prefix;

	prefix = ft_substr(str, 0, (size_t)(*i));
	if (!ft_strncmp(needle, "$", 2))
		expanded = ft_strjoin(prefix, "no PID");
	else
		expanded = ft_strjoin(prefix, get_value_from_env(envp, needle, NULL));
	free(prefix);
	return (expanded);
}

static char	*concat_expanded_string(char *expanded, char *str, int *i,
		char *needle)
{
	char	*extract;

	extract = ft_substr(str, (*i) + 1 + ft_strlen(needle), SIZE_T_MAX);
	expanded = ft_strjoin(expanded, extract);
	free(extract);
	return (expanded);
}

static char	*expand_str(char *str, int *i, char **envp)
{
	char	*needle;
	char	*expanded;

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

char	*ft_expand(char *line, char **envp, char expand_all)
{
	int		i;
	char	in_quotes;
	char	*expanded;

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
