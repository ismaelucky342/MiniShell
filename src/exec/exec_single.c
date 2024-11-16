/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:21:22 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/16 11:57:01 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Executes a single cmd, builtin or not.
 * 
 * @param node 
 * 	The node containing the information of the executed command
 * @param boogeyman
 * 	Pointer to the superstructure for env and memory purposes.
*/
t_bool	ft_exec_single_cmd(t_tree_node *node, t_minishell *boogeyman)
{
	if (isbuiltin(node->args[0]))
		if (ft_exec_builtin(node, boogeyman, KO) == FALSE)
			return (perror(node->args[0]), ft_hitman(boogeyman), FALSE);
	else
	{
		node->pid = fork();
		if (node->pid < 0)
			return (perror(node->args[0]), ft_hitman(boogeyman), FALSE);
		else if (node->pid == 0)
			ft_exec_ve(node, boogeyman);
		else
		{
			close(node->pipe_out);
		}
	}
}
