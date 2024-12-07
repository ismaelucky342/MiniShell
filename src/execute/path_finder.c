/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:52:55 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:45:15 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Checks if the given path is a relative path.
 *
 * @param path The path to check.
 * @return 1 if the path is relative, 0 otherwise.
 */
static int	ft_is_rel_path(char *path)
{
	if (!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "../", 3)
		|| !ft_strncmp(path, "/", 1))
		return (1);
	return (0);
}

/**
 * Executes a built-in shell command.
 *
 * @param node The current command node.
 * @param boogeyman The minishell context.
 * @param parent Indicates if the command is a parent process.
 */
void	ft_execbuiltin(t_tree_node *node, t_mini *boogeyman, char parent)
{
	node->exit_code = 0;
	node->is_builtin = 1;
	if (parent)
	{
		if (ft_file_redirs(node->redirs_lst,
				STDIN_FILENO, STDOUT_FILENO, boogeyman->envp))
		{
			node->exit_code = 1;
			return ;
		}
	}
	if (!ft_strncmp(node->args[0], "cd", 3))
		node->exit_code = ft_cd_builtin(node, boogeyman);
	else if (!ft_strncmp(node->args[0], "echo", 5))
		node->exit_code = ft_echo_builtin(node);
	else if (!ft_strncmp(node->args[0], "exit", 5))
		node->exit_code = ft_exit_builtin(node, boogeyman, parent);
	else if (!ft_strncmp(node->args[0], "pwd", 4))
		node->exit_code = ft_pwd_builtin(node, boogeyman->envp);
	else if (!ft_strncmp(node->args[0], "unset", 6))
		node->exit_code = ft_unset_builtin(node, boogeyman);
	else if (!ft_strncmp(node->args[0], "export", 7))
		node->exit_code = ft_export_builtin(node, boogeyman);
	if (!parent)
		exit(node->exit_code);
}

/**
 * Extracts the executable path for a given command.
 *
 * @param boogeyman The minishell context.
 * @param node The current command node.
 * @return The executable path if found, NULL otherwise.
 */
char	*extract_exec_path(t_mini *boogeyman, t_tree_node *node)
{
	int		pos;
	char	**split_path;
	char	*tmp;
	char	*path_plus_exec;

	if (!node->args[0] || ft_isbuiltin(node->args[0]))
		return (NULL);
	if (!(access(node->args[0], F_OK)) && ft_is_rel_path(node->args[0]))
		return (ft_strdup(node->args[0]));
	if (ft_is_rel_path(node->args[0]) || (!boogeyman->envp
			|| !*boogeyman->envp))
		return (NULL);
	split_path = ft_split(ft_get_from_env(boogeyman->envp, "PATH", NULL), ':');
	pos = 0;
	while (split_path[pos])
	{
		tmp = ft_strjoin(split_path[pos++], "/");
		path_plus_exec = ft_strjoin(tmp, node->args[0]);
		if (ft_strncmp(path_plus_exec, tmp, ft_strlen(tmp) + 1)
			&& !(access(path_plus_exec, F_OK)))
			return (ft_free_array(split_path), free(tmp), path_plus_exec);
		free(tmp);
		free(path_plus_exec);
	}
	return (ft_free_array(split_path), NULL);
}
