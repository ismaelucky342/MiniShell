/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:29:42 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:29:18 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	error(t_minishell *boogeyman)
{
	boogeyman->history_fd = -1;
	ft_putendl_fd(HIST_ERROR_MSG, STDERR_FILENO);
}

void	ft_init_file(t_minishell *boogeyman)
{
	char	*home_path;
	char	*full_path;

	home_path = get_value_from_env(boogeyman->envp, "HOME", NULL);
	if (!home_path || !*home_path)
	{
		error(boogeyman);
		return ;
	}
	full_path = ft_strjoin(home_path, HIST_TMP_BASE);
	if (!full_path)
		ft_memory_error(boogeyman);
	boogeyman->history_fd = open(full_path, O_CREAT | O_RDWR, 0644);
	free(full_path);
}

void	ft_h_fill(t_minishell *boogeyman)
{
	char	*line;
	char	*trimmed_line;

	line = get_next_line(boogeyman->history_fd);
	while (line)
	{
		trimmed_line = ft_strtrim(line, "\n");
		if (!trimmed_line)
			ft_memory_error(boogeyman);
		add_history(trimmed_line);
		free(line);
		free(trimmed_line);
		line = get_next_line(boogeyman->history_fd);
	}
}

void	ft_add_history(char *str, t_minishell *boogeyman)
{
	if (str && *str)
	{
		ft_putendl_fd(str, boogeyman->history_fd);
		add_history(str);
	}
}
