/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:12:29 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/07 22:30:49 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * exec_first_management
	- Manages the execution of the first command in a pipeline.
 * @param node: Pointer to the current command node.
 * @param boogeyman: Pointer to the minishell structure.
 * @param path: Pointer to the path of the executable.
 *
 * This function sets up the necessary fds,
	executes built-in commands,
 * removes env variables, and executes the command using execve.
 *
 * Return: 0 on success, 1 on failure.
 */
int	exec_first_management(t_tree_node *node, t_mini *boogeyman, char **path)
{
	ft_dup2(node->pipe_fds[1], STDOUT_FILENO);
	ft_close(node->pipe_fds[0]);
	ft_close(node->pipe_fds[1]);
	if (node->is_builtin)
		ft_execbuiltin(node, boogeyman, 0);
	ft_remove_env_variables(boogeyman);
	if (execve(*path, node->args, boogeyman->envp) < 0)
		return (perror(*path), freedom((void **)&*path), exit(126), 1);
	return (0);
}

/**
 * ft_exec_first_cmd - Executes the first command in a pipeline.
 * @param node: Pointer to the current command node.
 * @param boogeyman: Pointer to the minishell structure.
 * @param outfd: Pointer to the output fd.
 *
 * This function sets up the pipe, handles file redirections,
	checks for built-in commands,
 * and forks the process to execute the command.
 *
 * Return: 0 on success, 1 on failure.
 */
int	ft_exec_first_cmd(t_tree_node *node, t_mini *boogeyman, int *outfd)
{
	if (pipe(node->pipe_fds) == -1)
		return (perror("pipe"), 1);
	if (ft_file_redirs(node->redirs_lst, STDIN_FILENO, node->pipe_fds[1],
			boogeyman->envp))
		return (ft_close(node->pipe_fds[1]), *outfd = node->pipe_fds[0],
			node->exit_code = 1, 1);
	if (!node->args[0])
		return (ft_close(node->pipe_fds[1]), *outfd = node->pipe_fds[0],
			node->exit_code = 0, 1);
	node->path = extract_exec_path(boogeyman, node);
	node->is_builtin = ft_isbuiltin(node->args[0]);
	if (!node->path && !node->is_builtin)
		return (ft_no_path(node, 1, node->pipe_fds[1]),
			*outfd = node->pipe_fds[0], 0);
	ft_fork(node);
	if (node->pid)
		ft_close(node->pipe_fds[1]);
	if (!node->pid)
		return (exec_first_management(node, boogeyman, &node->path));
	freedom((void **)&node->path);
	*outfd = node->pipe_fds[0];
	return (0);
}

/**
 * ft_exec_mid_cmd - Executes a middle command in a pipeline.
 * @node: Pointer to the current command node.
 * @boogeyman: Pointer to the minishell structure.
 * @inputfd: Input fd.
 * @outfd: Pointer to the output fd.
 *
 * This function sets up the pipe, handles file redirections,
	checks for built-in commands,
 * and forks the process to execute the command.
 *
 * Return: 0 on success, 1 on failure.
 */
static int	ft_exec_mid_cmd(t_tree_node *node, t_mini *boogeyman, int inputfd,
		int *outfd)
{
	if (pipe(node->pipe_fds) == -1)
		return (perror("pipe"), 1);
	if (ft_file_redirs(node->redirs_lst, inputfd, node->pipe_fds[1],
			boogeyman->envp))
		return (ft_close(inputfd), ft_close(node->pipe_fds[1]),
			*outfd = node->pipe_fds[0], node->exit_code = 1, 1);
	if (!node->args[0])
		return (ft_close(inputfd), ft_close(node->pipe_fds[1]),
			*outfd = node->pipe_fds[0], node->exit_code = 0, 1);
	node->path = extract_exec_path(boogeyman, node);
	node->is_builtin = ft_isbuiltin(node->args[0]);
	if (!node->path && !node->is_builtin)
		return (ft_no_path(node, 1, node->pipe_fds[1]), ft_close(inputfd),
			*outfd = node->pipe_fds[0], 1);
	ft_fork(node);
	if (node->pid)
	{
		ft_close(node->pipe_fds[1]);
		ft_close(inputfd);
	}
	if (!node->pid)
		return (ft_dup2(inputfd, STDIN_FILENO), exec_first_management(node,
				boogeyman, &node->path));
	return (freedom((void **)&node->path), *outfd = node->pipe_fds[0], 0);
}

/**
 * ft_exec_last_cmd - Executes the last command in a pipeline.
 * @node: Pointer to the current command node.
 * @boogeyman: Pointer to the minishell structure.
 * @inputfd: Input fd.
 *
 * This function handles file redirections, checks for built-in commands,
 * and forks the process to execute the command.
 *
 * Return: 0 on success, 1 on failure.
 */
static int	ft_exec_last_cmd(t_tree_node *node, t_mini *boogeyman, int inputfd)
{
	if (ft_file_redirs(node->redirs_lst, inputfd, STDOUT_FILENO,
			boogeyman->envp))
		return (ft_close(inputfd), node->exit_code = 1, 1);
	if (!node->args[0])
		return (ft_close(inputfd), node->exit_code = 0, 1);
	node->path = extract_exec_path(boogeyman, node);
	if (!node->path && !ft_isbuiltin(node->args[0]))
		return (ft_no_path(node, 1, STDOUT_FILENO), ft_close(inputfd), 0);
	ft_fork(node);
	node->is_builtin = ft_isbuiltin(node->args[0]);
	if (node->pid)
		ft_close(inputfd);
	if (!node->pid)
	{
		ft_dup2(inputfd, STDIN_FILENO);
		if (node->is_builtin)
			ft_execbuiltin(node, boogeyman, 0);
		ft_remove_env_variables(boogeyman);
		if (execve(node->path, node->args, boogeyman->envp) == -1)
			return (ft_close(inputfd), perror(node->path), freedom((void **)&node->path),
				exit(126), 1);
	}
	freedom((void **)&node->path);
	return (0);
}

/**
 * ft_pipes_interpreter - Interprets and executes a pipeline of commands.
 * @tree_node: Pointer to the AST tree node containing the command list.
 * @boogeyman: Pointer to the minishell structure.
 * @last_pid: Pointer to store the PID of the last executed command.
 *
 * This function iterates through the command list,
	executing each command in the pipeline.
 * It handles built-in commands, sets up pipes, and manages fds.
 *
 * Return: Pointer to the last executed command node.
 */
t_tree_node	*ft_pipes_interpreter(t_ast_tree *tree_node, t_mini *boogeyman,
		int *last_pid)
{
	t_tree_node	*lst;
	int			inputfd;
	int			outputfd;

	inputfd = 0;
	outputfd = 0;
	lst = tree_node->cmd_list;
	if (!lst->next && lst->args[0] && ft_isbuiltin(lst->args[0]))
	{
		ft_execbuiltin(lst, boogeyman, 1);
		lst->is_builtin = 1;
		return (lst);
	}
	else if (!lst->next)
		return (ft_exec_single_cmd(lst, boogeyman), *last_pid = lst->pid, lst);
	ft_exec_first_cmd(lst, boogeyman, &inputfd);
	lst = lst->next;
	while (lst->next)
	{
		ft_exec_mid_cmd(lst, boogeyman, inputfd, &outputfd);
		inputfd = outputfd;
		lst = lst->next;
	}
	return (ft_exec_last_cmd(lst, boogeyman, inputfd), *last_pid = lst->pid,
		lst);
}
