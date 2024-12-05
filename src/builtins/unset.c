/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:53:48 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:30:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_unset_builtin - Unsets environment variables specified in the command arguments.
 * @node: A pointer to the tree node containing the command and its arguments.
 * @boogeyman: A pointer to the minishell structure containing the environment variables.
 *
 * This function marks the node as a builtin command and iterates through the 
 * command arguments starting from the second argument. For each argument, it 
 * calls the ft_remove_env function to remove the corresponding environment variable 
 * from the minishell's environment.
 *
 * Return: Always returns 0.
 */
int	ft_unset_builtin(t_tree_node *node, t_minishell *boogeyman)
{
	int	i;

	i = 0;
	node->is_builtin = 1;
	while (node->args[++i])
		ft_remove_env(boogeyman, node->args[i]);
	return (0);
}
