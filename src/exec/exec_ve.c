/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:02:10 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/28 16:43:03 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_exedirs(t_list *redirs, t_minishell *boogeyman)
{
	t_redirection_token		*token;
	
	while (redirs)
	{
		token = (t_redirection_token *)redirs->data;
		/* TODO: Figure out WHAT THE HELL ANY OF THIS MMMMMMMEEEEEEEEEEAAAAAAAAAANNNNNNSSSSSSSSS*/
		redirs = redirs->next;
	}
	return(FALSE);
}

t_bool	ft_exec_ve(t_tree_node *node, t_minishell *boogeyman, t_bool single)
{
	char	*cmd_path;
	char	**env;
	char	**args;
	
	env = boogeyman->envp;
	boogeyman->envp = NULL;
	args = node->args;
	node->args = NULL;
	if (single == FALSE && node->redir_list)
		if (ft_exedirs(node->redir_list, boogeyman) == FALSE)
			exit(EXIT_FAILURE);
	cmd_path = ft_where_is_comm_b(args[0], env);
	ft_hitman(boogeyman);
	execve(cmd_path, args, env);
	perror(cmd_path);
	ft_array_free(env);
	ft_array_free(args);
	free(cmd_path);
	exit(EXIT_FAILURE);
}
