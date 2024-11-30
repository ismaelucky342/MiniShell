/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:59:59 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/30 11:02:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit;

static void	handle_heredoc_child_process(char *delim, char *f_name, int fd)
{
	signal(SIGINT, SIG_DFL); // Restaurar señales en el hijo
	handle_heredoc_input(delim, fd);
	free(delim);
	free(f_name);
	close(fd);
	exit(0);
}

static int	handle_single_heredoc(char **str, int *i, char **f_name)
{
	int		fd;
	int		pid;
	char	*delim;

	fd = create_temp_heredoc(str, i, &delim, f_name);
	if (fd == -1 || !g_exit)
	{
		free(delim);
		return (KO);
	}
	pid = fork();
	if (pid < 0)
	{
		free(delim);
		return (KO);
	}
	if (pid == 0)
		handle_heredoc_child_process(delim, *f_name, fd);
	waitpid(pid, &g_exit, 0);
	free(delim);
	close(fd);
	if (g_exit == 0)
		return (OK);
	else
		return (KO);
}

int	handle_multiple_heredocs(char **str)
{
	int		i;
	char	*tmp;
	char	*f_name;

	i = 0;
	while ((*str)[i])
	{
		if (is_heredoc_trigger(*str, &i))
		{
			if (handle_single_heredoc(str, &i, &f_name) == KO)
			{
				free(f_name);
				return (KO);
			}
			free(f_name);
		}
		else
			i++;
	}
	return (OK);
}

int	is_heredoc_trigger(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		*i += 2;
		return (1);
	}
	return (0);
}
