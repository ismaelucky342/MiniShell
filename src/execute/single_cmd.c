/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:11:17 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:49:08 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Executes a single command
	1. Try opening files, redirect loops
	2. Redirect loop for pipes
	3. Find executable, some builtins may be runned in parent process
	4. fork if necesary, then execute 
*/
int	ft_exec_single_cmd(t_tree_node *node, t_mini *boogeyman)
{
	if (ft_file_redirs(node->redirs_lst, STDIN_FILENO, STDOUT_FILENO,
			boogeyman->envp))
		return (node->exit_code = 1, 1);
	if (!node->args[0])
		return (1);
	node->path = extract_exec_path(boogeyman, node);
	if (!node->path)
		return (ft_no_path(node, 0, 0), 0);
	ft_fork(node);
	if (node->pid)
		ft_close(node->pipe_fds[0]);
	if (!node->pid)
	{
		ft_remove_env_variables(boogeyman);
		if (execve(node->path, node->args, boogeyman->envp) == -1)
			return (perror(node->path), free(node->path), exit(126), 1);
	}
	free(node->path);
	return (0);
}
