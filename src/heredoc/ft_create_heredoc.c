/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:42:42 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:43:11 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

/**
 * Creates heredoc files based on the given string.
 *
 * @param str The string to be checked for heredocs.
 * @return 1 if there is an error creating heredocs, 0 otherwise.
 */
int	ft_create_heredocs(char **str)
{
	int		i;
	char	*f_name;

	i = 0;
	f_name = NULL;
	while ((*str)[i] && g_is_exec)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			state_quote_delimiter(*str, &i, (*str)[i]);
		if (!ft_strncmp("<<", &(*str)[i], 2))
			if (ft_heredoc(str, &i, &f_name))
				return (1);
		waitpid(-1, NULL, 0);
		if (f_name)
		{
			if (!g_is_exec)
				unlink(f_name);
			free(f_name);
			f_name = NULL;
		}
		if ((*str)[i])
			++i;
	}
	return (0);
}