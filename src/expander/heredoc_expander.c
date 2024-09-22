/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:19:00 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:45:33 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*generate_tmp_filename(int index)
{
	char	*tmp;
	char	*name;

	tmp = ft_itoa(index);
	if (!tmp)
		return (NULL);
	name = ft_strjoin(H_DOC_TMP_BASE, tmp);
	free(tmp);
	return (name);
}

char	*get_tmp_filename(void)
{
	char	*name;
	int		i;

	i = 1;
	while (i <= 1000)
	{
		name = generate_tmp_filename(i);
		if (!name)
			return (NULL);
		if (access(name, F_OK) != 0)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}

static void	handle_heredoc_error(t_redirection_token *tok)
{
	perror(tok->name);
	free(tok->name);
	exit(1);
}

static int	open_and_write_heredoc(int o_fd, t_redirection_token *tok,
		char **envp)
{
	int		fd;
	char	*line;
	char	*exp;

	unlink(tok->name);
	free(tok->name);
	tok->name = get_tmp_filename();
	if (!tok->name)
	{
		ft_putendl_fd("No heredoc tmp file available!", STDERR_FILENO);
		return (exit(1), -1);
	}
	fd = open(tok->name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_heredoc_error(tok);
	line = get_next_line(o_fd);
	while (line)
	{
		exp = ft_expand(line, envp, 1);
		ft_putstr_fd(exp, fd);
		free(line);
		free(exp);
		line = get_next_line(o_fd);
	}
	return (fd);
}

int	ft_expand_heredoc(int o_fd, t_redirection_token *tok, char **envp)
{
	return (open_and_write_heredoc(o_fd, tok, envp));
}
