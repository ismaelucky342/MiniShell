/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:11:53 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/27 11:49:59 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief
 * Finds the "PATH=" entry in env and returns a split of all routes it contains.
 * @param env
 * 	NULL-terminated array containing an array of environment variables.
 * @return
 * 	returns a split of the "PATH=" entry, or NULL if said entry doesn't exist.
 */
static char	**path_array_b(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path != NULL)
			return (ft_split(path + 5, ':'));
		i++;
	}
	return (NULL);
}

/**
 * @brief
 * 	Finds the path containing the location of the command
 * @param command
 * 	String containing the command to search
 * @param env
 * 	NULL-terminated array containing an array of environment variables.
 * @return
 * 	Path of the command.
 * 	If the introduced command is a route, returns a dup of it.
 * 	If the command file isn't in env, returns the original introduced command.
 */
char	*ft_where_is_comm_b(char *command, char **env)
{
	char	*pth_prog;
	char	**path_arr;
	char	*cmd_slash;
	int		i;

	if (command && ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_arr = path_array_b(env);
	if (!path_arr)
		return (ft_strdup(command));
	cmd_slash = ft_strjoin("/", command);
	if (!cmd_slash)
		return (NULL);
	i = 0;
	while (path_arr[i] != NULL)
	{
		pth_prog = ft_strjoin(path_arr[i ++], cmd_slash);
		if (access(pth_prog, F_OK) != -1 && access(pth_prog, X_OK) != -1)
			return (arr_freer(path_arr), free(cmd_slash), pth_prog);
		free(pth_prog);
	}
	return (arr_freer(path_arr), ft_strdup(command));
}
