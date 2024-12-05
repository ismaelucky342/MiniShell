/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:19:31 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 11:11:50 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fork(t_tree_node *node)
{
	node->pid = fork();
	if (node->pid < 0)
	{
		perror("fork");
		exit(1);
	}
}

/*
	Prints command not found, then
	sets exit code as 127 and closes pipes
*/
int	ft_no_path(t_tree_node *node, int close, int fd)
{
	ft_putstr_fd("MiniShell: command not found: ", STDERR_FILENO);
	if (node->args[0])
		ft_putendl_fd(node->args[0], STDERR_FILENO);
	node->exit_code = 127;
	if (close)
		ft_close(fd);
	return (0);
}




