/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:53:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/11 14:56:03 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_pwd_builtin - A function to print the current working directory.
 * @node: A pointer to a tree node structure (unused in this function).
 * @envp: An array of strings representing the env variables.
 *
 * This function retrieves the current working directory from the env
 * variables using the key "PWD". If the "PWD" variable is found and is not
 * empty, it prints the directory to the standard output. If the "PWD" variable
 * is not found or is empty, it prints an error message to the standard error.
 *
 * Return: Always returns 0.
 */
int	ft_pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
		ft_putendl_fd("PWD error", STDERR_FILENO);
	free(pwd);
	return (0);
}
