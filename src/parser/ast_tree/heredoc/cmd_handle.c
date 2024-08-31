/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:52:19 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:52:21 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	cmd_handle(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->redir[i])
	{
		if (cmd->redir_type[i] >= 3)
		{
			cmd->redir[i] = expander(cmd->redir[i]);//dani necesito esto
			if (cmd->redir_type[i] == 4)
				cmd->redir_type[i] = heredoc(cmd->redir[i]);
			else
				cmd->redir_type[i] = -heredoc(cmd->redir[i]);
			free(cmd->redir[i]);
			cmd->redir[i] = NULL;
			if (cmd->redir_type[i] == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
