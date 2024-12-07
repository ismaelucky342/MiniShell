/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:42:42 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 22:30:49 by dgomez-l         ###   ########.fr       */
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
			freedom((void **)&f_name);
			f_name = NULL;
		}
		if ((*str)[i])
			++i;
	}
	return (0);
}
