/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:53:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:58:25 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * cd_management - Changes the current working directory and updates environment variables.
 * @boogeyman: A pointer to the minishell structure containing environment variables.
 * @path: A double pointer to the path to change to.
 *
 * This function changes the current working directory to the path specified by @path.
 * It updates the "OLDPWD" and "PWD" environment variables accordingly and updates the shell prompt.
 * If the directory change fails, it prints an error message and returns 1.
 * 
 * Return: 0 on success, 1 on failure.
 */

static int	cd_management(t_minishell *boogeyman, char **path)
{
	char	*cwd;

	cwd = ft_get_from_env(boogeyman->envp, "PWD", NULL);
	if (chdir(*path) == -1)
	{
		perror(*path);
		return (1);
	}
	*path = ft_strjoin("OLDPWD=", cwd);
	ft_add_to_env(boogeyman, *path);
	free(*path);
	cwd = cwd_str_status();
	if (!cwd)
		return (1);
	*path = ft_strjoin("PWD=", cwd);
	ft_add_to_env(boogeyman, *path);
	free(*path);
	free(cwd);
	update_prompt(boogeyman); // Update the prompt after changing directory
	return (0);
}

/**
 * ft_cd_builtin - Builtin function to change the current working directory.
 * @node: A pointer to the tree node containing command arguments.
 * @boogeyman: A pointer to the minishell structure containing environment variables.
 *
 * This function handles the 'cd' command in the minishell. It checks the arguments provided
 * and determines the target directory. If no directory is specified, it defaults to the "HOME"
 * environment variable. It then calls cd_management to perform the directory change.
 * If too many arguments are provided, it prints an error message and returns 1.
 * 
 * Return: 0 on success, 1 on failure.
 */
int	ft_cd_builtin(t_tree_node *node, t_minishell *boogeyman)
{
	char	*path;

	if (node->args[0] && node->args[1])
	{
		if (node->args[2] != NULL)
		{
			ft_putendl_fd("MiniShell: cd: too many arguments", STDERR_FILENO);
			return (1);
		}
		path = node->args[1];
	}
	else
	{
		path = ft_get_from_env(boogeyman->envp, "HOME", NULL);
		if (!*path)
			return (ft_putendl_fd("HOME is not set", STDERR_FILENO), 1);
	}
	return (cd_management(boogeyman, &path));
}
