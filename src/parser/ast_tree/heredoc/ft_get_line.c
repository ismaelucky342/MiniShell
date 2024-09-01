/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:52:29 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:52:30 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	*ft_get_line(void)
{
	char	*line;
	char	*tmp;

	if (isatty(fileno(stdin)) && !DEBUG)
		line = readline("> ");
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		if (tmp)
		{
			line = ft_strtrim(tmp, "\n");
			free(tmp);
		}
		else
			line = NULL;
	}
	return (line);
}

