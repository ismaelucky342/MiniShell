/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:23:29 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/28 14:55:19 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
	* Executes the "export" command.
	* @param
	* *node The tree node that's being executed.
	* @param
	* *boogeyman Superstructure pointer for env & memory freeing purposes.
	* @returns
	* returns the status of the executed command.
*/
int	ft_export(t_tree_node *node, t_minishell *boogeyman)
{
	(void)node;
	(void)boogeyman;
	return (0);
}
