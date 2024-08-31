/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:52:47 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:52:48 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int redir_handler(t_redir *redir)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = redir->redirects;
	while (cmd->redir[i])
	{
		if (cmd->redir_type[i] >= 3)
		{
			cmd->redir[i] = expander(cmd->redir[i]);//taki taki rumba
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
	if (redir->next)
		ast_walker(redir->next, redir->type);
	return (0);
}
