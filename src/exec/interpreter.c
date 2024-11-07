/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:19:29 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/27 17:42:29 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Interprets the priority tree, executing the commands within.
 * 
 * @param node
 * Base of the ast tree of commands that should be executed.
 * @param boogeyman
 * Superstructure pointer for env and memory reasons.
 */
t_tree_node	*ft_interpreter(t_ast_tree *node, t_minishell *boogeyman,
	int *lastpid)
{
	t_tree_node		*list = node->cmd_list;
	int				fds[2];

	if (!list->next)
	{
		ft_exec_single_cmd(list, boogeyman);
		*lastpid = list->pid;
		return (list);
	}
	if (ft_exec_first_cmd(list, boogeyman, &fds[1]) == KO)
		return (NULL);
	list = list->next;
	fds[0] = fds[1];
	while (list->next)
	{
		if (ft_exec_mid_cmd(list, boogeyman, fds[0], &fds[1]) == KO)
			return (NULL);
		fds[0] = fds[1];
		list = list->next;
	}
	if (ft_exec_last_cmd(list, boogeyman, fds[0]) == KO)
		return (NULL);
	*lastpid = list->pid;
	return (list);
}
