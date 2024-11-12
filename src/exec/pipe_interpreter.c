/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:19:29 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/12 12:26:48 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Interprets the priority tree, executing piped commands within.
 * 
 * @param node
 * Base of the ast tree of commands that should be executed.
 * @param boogeyman
 * Superstructure pointer for env and memory reasons.
 */
t_tree_node	*ft_pipes_interpreter(t_ast_tree *node, t_minishell *boogeyman,
	int *lastpid)
{
	t_tree_node		*list = node->cmd_list;
	int				fds[2];

	if (!list->next)
	{
		if (ft_exec_single_cmd(list, boogeyman) == KO)
			return (ft_hitman(boogeyman), NULL);
		*lastpid = list->pid;
		return (list);
	}
	if (ft_exec_first_cmd(list, boogeyman, &fds[1]) == KO)
		return (ft_hitman(boogeyman), NULL);
	list = list->next;
	fds[0] = fds[1];
	while (list->next)
	{
		if (ft_exec_mid_cmd(list, boogeyman, fds[0], &fds[1]) == KO)
			return (ft_hitman(boogeyman), NULL);
		fds[0] = fds[1];
		list = list->next;
	}
	if (ft_exec_last_cmd(list, boogeyman, fds[0]) == KO)
		return (ft_hitman(boogeyman), NULL);
	*lastpid = list->pid;
	return (list);
}
