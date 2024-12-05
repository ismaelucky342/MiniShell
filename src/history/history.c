/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:17:16 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:41:19 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_history_filler - Reads lines from the history file descriptor and adds them to the history.
 * @boogeyman: A pointer to the t_minishell structure containing the history file descriptor.
 *
 * This function reads each line from the file descriptor stored in the t_minishell structure,
 * trims the newline character from the end of each line, and adds the trimmed line to the history.
 * If memory allocation for the trimmed line fails, the function calls ft_memory_err_exit to handle
 * the error. The function continues reading and processing lines until the end of the file is reached.
 */
void	ft_history_filler(t_minishell *boogeyman)
{
	char	*line;
	char	*trim;

	line = get_next_line(boogeyman->history_fd);
	while (line)
	{
		trim = ft_strtrim(line, "\n");
		if (!trim)
			ft_memory_err_exit(boogeyman);
		add_history(trim);
		free(line);
		free(trim);
		line = get_next_line(boogeyman->history_fd);
	}
}

/**
 * Adds a command to the shell history.
 *
 * This function writes the given command string to the history file descriptor
 * and also adds it to the in-memory history list.
 *
 * @param str The command string to be added to the history.
 * @param boogeyman A pointer to the t_minishell structure containing the history file descriptor.
 */
void	ft_add_history(char *str, t_minishell *boogeyman)
{
	ft_putendl_fd(str, boogeyman->history_fd);
	add_history(str);
}
