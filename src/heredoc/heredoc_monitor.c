/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:23:23 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:51:54 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

/**
 * @brief Substitutes a delimeter in a string with a space and
		updates the string.
 *
 * This function takes a string and substitutes a delimiter at a given position
 * with a space. It then updates the original string with the new value.
 *
 * @param str Pointer to the string to be updated.
 * @param j Position of the delimiter in the string.
 * @param tmp Temporary string used for joining.
 * @param tmp2 Temporary string used for substring extraction.
 */
void	delim_subs(char **str, int j, char *tmp, char *tmp2)
{
	free(tmp);
	tmp = ft_strjoin(tmp2, " ");
	free(tmp2);
	tmp2 = ft_substr(*str, j, SIZE_T_MAX);
	free(*str);
	*str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
}

/**
 * @brief Monitors input lines for a heredoc until a delimiter is encountered.
 *
 * This function reads lines from the standard input and writes them to a file
 * descriptor until a line matching the delimiter is encountered.
 *
 * @param line Pointer to the input line.
 * @param prompt Prompt to be displayed for readline.
 * @param delim Delimiter string to stop reading.
 * @param fd fd to write the lines to.
 */
void	heredoc_monitor(char **line, char *prompt, char *delim, int *fd)
{
	while ((*line) && ft_strncmp((*line), delim, ft_strlen(delim) + 1))
	{
		ft_putendl_fd((*line), *fd);
		free((*line));
		(*line) = NULL;
		(*line) = readline(prompt);
	}
}
