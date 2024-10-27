/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:33:18 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/05/22 11:37:39 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**path_array_b(char **env)
{
	int		i;
	char	*path;
	char	**path_split;

	i = 0;
	while (env[i] != NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path != NULL)
		{
			path_split = ft_split(path, ':');
			if (!path_split)
				return (NULL);
			path = path_split[0];
			path_split[0] = ft_strdup(&path[5]);
			free(path);
			return (path_split);
		}
		i++;
	}
	return (NULL);
}

static char	*where_is_comm_b(char *command, char **env)
{
	char	*pth_prog;
	char	**path_arr;
	int		i;

	if (command && ft_strchr(command, '/'))
		return (ft_strdup(command));
	command = ft_strjoin("/", command);
	if (!command)
		return (NULL);
	path_arr = path_array_b(env);
	if (!path_arr)
		return (command);
	i = 0;
	while (path_arr[i] != NULL)
	{
		pth_prog = ft_strjoin(path_arr[i ++], command);
		if (access(pth_prog, F_OK) != -1 && access(pth_prog, X_OK) != -1)
			return (arr_freer(path_arr), free(command), pth_prog);
		free(pth_prog);
	}
	return (arr_freer(path_arr), command);
}

static int	first_pipe(int *fds, t_index *index)
{
	if (index->i != 0)
		return (1);
	if (fds[0] < 0 || dup2(fds[0], STDIN_FILENO) < 0)
	{
		if (fds[0] >= 0)
			close(fds[0]);
		fds[0] = open(index->in, O_RDONLY);
		if (fds[0] >= 0)
			close(fds[0]);
		return (perror(index->in), 1);
	}
	if (dup2(fds[1], STDOUT_FILENO) < 0)
		return (1);
	return (0);
}

static int	last_pipe(int *fds, t_index *index)
{
	int		*pipe;

	if (index->i == 0)
		return (1);
	pipe = &fds[(index->i * 2) - 1];
	if (dup2(pipe[1], STDIN_FILENO) < 0)
		return (1);
	if (pipe[2] < 0 || dup2(pipe[2], STDOUT_FILENO) < 0)
	{
		if (pipe[2] >= 0)
			close(pipe[2]);
		pipe[2] = open(index->out, O_WRONLY);
		if (pipe[2] >= 0)
			close(pipe[2]);
		perror(index->out);
		return (1);
	}
	return (0);
}

int	execution(int *fds, char *arg, char **env, t_index *index)
{
	char	*pth_prog;
	char	*command;
	char	**arguments;
	int		i[2];

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	i[0] = first_pipe(fds, index);
	i[1] = last_pipe(fds, index);
	fd_arr_closer(fds, index->fd_count - 1);
	if (index->bonus)
		free(fds);
	if (i[0] && i[1])
		exit(EXIT_FAILURE);
	arguments = ft_split(arg, ' ');
	if (!arguments)
		exit(EXIT_FAILURE);
	command = arguments[0];
	pth_prog = where_is_comm_b(command, env);
	execve(pth_prog, arguments, env);
	perror(arguments[0]);
	free(pth_prog);
	arr_freer(arguments);
	exit(EXIT_FAILURE);
}
