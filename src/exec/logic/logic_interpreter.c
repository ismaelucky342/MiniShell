/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_interpreter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:26:34 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/28 14:56:57 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Interprets the priority tree, executing piped commands within.
 * 
 * @param node
 * Base of the ast tree of commands that should be executed.
 * @param boogeyman
 * Superstructure pointer for env and memory reasons.
 */
t_tree_node	*ft_logic_interpreter(t_ast_tree *node, t_minishell *boogeyman,
	int *lastpid)
{
	(void)node;
	(void)boogeyman;
	(void)lastpid;
	return (node->cmd_list);
}