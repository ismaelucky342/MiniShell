/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:20:09 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/28 15:03:11 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if the introduced path is an absolute or relative path
 * @param path
 *  The user-introduced command string that will be checked
 * @return
 * 1 if the introduced path is an absolute or relative path. Otherwise, 0
*/
int	ft_is_a_path(char *path)
{
	if (ft_strchr(path, '/'))
		return (1);
	return (0);
}

/**
 * @brief Executes a builtin command.
 * 
 * @param node
 *  The node of the command to execute.
 * @param boogeyman
 *  Pointer to the superstructure for env and memory purposes.
 * @param parent
 * 	Boolean that dictates if the command is executed in the parent process.
 */
t_bool	ft_exec_builtin(t_tree_node *node, t_minishell *boogeyman, char parent)
{
	(void)node;
	(void)boogeyman;
	(void)parent;
	if (ft_strcmp(node->args[0], "cd"))
	{
		
	}
	return(FALSE);
}