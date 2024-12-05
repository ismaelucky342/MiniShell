/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:53:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:30:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_pwd_builtin - A function to print the current working directory.
 * @node: A pointer to a tree node structure (unused in this function).
 * @envp: An array of strings representing the environment variables.
 *
 * This function retrieves the current working directory from the environment
 * variables using the key "PWD". If the "PWD" variable is found and is not
 * empty, it prints the directory to the standard output. If the "PWD" variable
 * is not found or is empty, it prints an error message to the standard error.
 *
 * Return: Always returns 0.
 */
int	ft_pwd_builtin(t_tree_node *node, char **envp)
{
	char	*pwd;

	(void) node;
	pwd = ft_get_from_env(envp, "PWD", NULL);
	if (*pwd)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
		ft_putendl_fd("PWD error", STDERR_FILENO);
	return (0);
}
