/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:53:48 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:39:10 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_unset_builtin
	- Unsets env variables specified in the command arguments.
 * @param node: A pointer to the tree node containing the command and
		its arguments.
 * @param boogeyman: A pointer to the minishell structure containing the
		env variables.
 *
 * This function marks the node as a builtin command and iterates through the 
 * command arguments starting from the second argument. For each argument, it 
 * calls the ft_remove_env function to remove the corresponding
		env variable 
 * from the minishell's env.
 *
 * Return: Always returns 0.
 */
int	ft_unset_builtin(t_tree_node *node, t_mini *boogeyman)
{
	int	i;

	i = 0;
	node->is_builtin = 1;
	while (node->args[++i])
		ft_remove_env(boogeyman, node->args[i]);
	return (0);
}
