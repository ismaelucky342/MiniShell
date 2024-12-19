/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:21:53 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/18 18:03:39 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_open(t_rtoken *f_tok)
{
	int		fd;

	fd = -1;
	if (f_tok->redir_type == M_INFILE || f_tok->redir_type == M_HEREDOC)
		fd = open(f_tok->file_name, O_RDONLY);
	else if (f_tok->redir_type == M_OUT)
		fd = open(f_tok->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (f_tok->redir_type == M_CONCAT_OUT_ST)
		fd = open(f_tok->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(f_tok->file_name);
	return (fd);
}

void	ft_close(int fd)
{
	if (fd < 0)
		return ;
	if (close(fd) == -1)
		perror("close");
}

void	ft_dup2(int oldfd, int newfd)
{
	int		status;

	status = dup2(oldfd, newfd);
	if (status == -1)
		perror("dup2");
}

void	is_quote(char *str, int *i, int *last)
{
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		state_quote_delimiter(str, i, str[*i]);
		if (str[*i] == '\'' || str[*i] == '\"')
			++(*i);
	}
	else if (str[*i] == '(')
		ft_brackets(str, i);
	else
		++(*i);
	if ((str[*i] == '&' && str[*i + 1] == '&') || (str[*i] == '|' && str[*i
				+ 1] == '|') || str[*i] == ';')
		*last = (*i);
}

int	ft_file_redirs(t_list *files, int input_fd, int output_fd, char **envp)
{
	int		fd;

	while (files)
	{
		fd = ft_open((t_rtoken *)(files->content));
		if (fd < 0)
			return (1);
		if (((t_rtoken *)(files->content))->redir_type == M_INFILE)
			ft_dup2(fd, input_fd);
		else if (((t_rtoken *)(files->content))->redir_type == M_HEREDOC)
		{
			fd = ft_expand_str_heredoc(fd, (t_rtoken *)(files->content), envp);
			ft_close(fd);
			fd = ft_open((t_rtoken *)(files->content));
			if (fd < 0)
				return (1);
			ft_dup2(fd, input_fd);
			unlink(((t_rtoken *)(files->content))->file_name);
		}
		else
			ft_dup2(fd, output_fd);
		ft_close(fd);
		files = files->next;
	}
	return (0);
}
