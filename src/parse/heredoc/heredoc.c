/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:27:16 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:59:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit;

static char	*extract_delimiter(char **str, int *i)
{
	int	j;

	j = *i;
	while (ft_isspace((*str)[*i]))
		(*i)++;
	j = *i;
	while ((*str)[j] && !ft_isspace((*str)[j])
		&& !ft_is_reserved_char((*str)[j]) && (*str)[j] != '('
		&& (*str)[j] != ')')
	{
		if ((*str)[j] == '\'' || (*str)[j] == '"')
			skip_to_delimiter(*str, &j, (*str)[j]);
		else
			j++;
	}
	if (j == *i)
	{
		return (NULL);
	}
	return (ft_substr(*str, *i, j - *i));
}

static void	substitute_and_create_new_string(char **str, int *i, char *new_name)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(*str, 0, *i);
	tmp2 = ft_strjoin(tmp, new_name);
	new_string(str, *i, tmp, tmp2);
	free(tmp);
	free(tmp2);
}

static int	create_temp_heredoc(char **str, int *i, char **delim, char **f_name)
{
	int	fd;

	*f_name = get_tmp_filename();
	if (!*f_name)
	{
		ft_putendl_fd("No heredoc tmp file available!", STDERR_FILENO);
		exit(1);
	}
	fd = open(*f_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(*f_name);
		free(*f_name);
		exit(1);
	}
	*delim = extract_delimiter(str, i);
	if (!*delim)
	{
		ft_close(fd);
		return (-1);
	}
	substitute_and_create_new_string(str, i, *f_name);
	*i += 2;
	return (fd);
}

static void	handle_heredoc_input(char *delim, int fd)
{
	char	*line;
	char	*prompt;
	char	*full_prompt;

	prompt = ft_strjoin("here_doc (", delim);
	full_prompt = ft_strjoin(prompt, ") > ");
	free(prompt);
	line = readline(full_prompt);
	heredoc_input(&line, full_prompt, delim, &fd);
	free(line);
	free(full_prompt);
}

int	ft_heredoc(char **str, int *i, char **f_name)
{
	int		fd;
	int		pid;
	char	*delim;

	fd = create_temp_heredoc(str, i, &delim, f_name);
	if (fd == -1 || !g_exit)
	{
		free(delim);
		return (1);
	}
	pid = fork();
	free(delim);
	if (pid < 0)
		return (1);
	else
		return (0);
	signal(SIGINT, SIG_DFL);
	handle_heredoc_input(delim, fd);
	free(delim);
	free(*f_name);
	ft_close(fd);
	exit(0);
}
