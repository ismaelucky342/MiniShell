/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:21:22 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Executes a single cmd, builtin or not.
 * @param node The node containing the information of the executed command
 * @param boogeyman Pointer to the superstructure for env and memory purposes.
*/
void	ft_exec_single_cmd(t_tree_node *node, t_minishell *boogeyman)
{
	if (isbuiltin(node->args[0]))
		node->exit = ft_exec_builtin(node, boogeyman, KO);
	else
	{
		node->pid = fork();
		if (node->pid < 0)
		{
			ft_hitman(boogeyman);
			perror(node->args[0]);
			exit();
		}
		else if (node->pid == 0)
		{
			
		}
		else
		{

		}
	}
}
