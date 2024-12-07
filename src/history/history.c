/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:17:16 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:51:59 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_history_filler
	- Reads lines from the history fd and adds them to the history.
 * @param boogeyman: A pointer to the t_mini structure containing the
		history fd.
 *
 * This function reads each line from the fd stored in the
		t_mini structure,
 * trims the newline character from the end of each line,
	and adds the trimmed line to the history.
 * If memory allocation for the trimmed line fails,
	the function calls ft_memory_err_exit to handle
 * the error. The function continues reading and processing lines until
		the end of the file is reached.
 */
void	ft_history_filler(t_mini *boogeyman)
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
 * This function writes the given command string to the history fd
 * and also adds it to the in-memory history list.
 *
 * @param str The command string to be added to the history.
 * @param boogeyman A pointer to the t_mini structure containing the history fd.
 */
void	ft_add_history(char *str, t_mini *boogeyman)
{
	ft_putendl_fd(str, boogeyman->history_fd);
	add_history(str);
}
