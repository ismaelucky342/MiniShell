/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:23:06 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/31 14:23:08 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
	* Executes the "env" command, displaying the entire array of environment variables
	* @param
	* *node The tree node that's being executed.
	* @param
	* *boogeyman Superstructure pointer for env & memory freeing purposes.
	* @returns
	* returns the status of the executed command.
*/
int	ft_env(t_tree_node *node, t_minishell *boogeyman)
{
	boogeyman->envp;
	return (0);
}
