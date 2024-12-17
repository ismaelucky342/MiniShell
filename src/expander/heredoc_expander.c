/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:34:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/15 17:51:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_expand_str_heredoc
	- Expands a heredoc string and writes it to a temporary file.
 * @o_fd: The fd to read the original heredoc from.
 * @tok: A pointer to a t_rtoken structure containing the heredoc metadata.
 * @envp: The env variables used for expanding the heredoc string.
 *
 * This function reads lines from the original heredoc fd, expands
 * any env variables within those lines, and writes the expanded lines
 * to a new temporary file. The temporary file's name is stored in the
		tok structure.
 * If any errors occur during this process,
	appropriate error messages are printed
 * and the function exits with a failure status.
 *
 * Return: The fd of the new temporary file containing the
		expanded heredoc,
 *         or -1 if an error occurs.
 */
int	ft_expand_str_heredoc(int o_fd, t_rtoken *tok, char **envp)
{
	int		fd;
	char	*line;
	char	*exp;

	unlink(tok->file_name);
	freedom((void **)&tok->file_name);
	tok->file_name = tmp_filename();
	if (!tok->file_name)
		return (ft_putendl_fd("No heredoc tmp file available!", 2), exit(1),
			-1);
	fd = open(tok->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(tok->file_name), freedom((void **)&tok->file_name),
			exit(1), -1);
	line = get_next_line(o_fd);
	while (line)
	{
		exp = ft_expand_str(line, envp, 1);
		ft_putstr_fd(exp, fd);
		freedom((void **)&line);
		freedom((void **)&exp);
		line = get_next_line(o_fd);
	}
	return (fd);
}
