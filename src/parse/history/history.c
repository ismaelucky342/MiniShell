/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:29:42 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:16:56 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	error(t_minishell *sack)
{
	sack->history_fd = -1;
	ft_putendl_fd(HIST_ERROR_MSG, STDERR_FILENO);
}

void	ft_init_file(t_minishell *sack)
{
	char	*home_path;
	char	*full_path;

	home_path = get_value_from_env(sack->envp, "HOME", NULL);
	if (!home_path || !*home_path)
	{
		error(sack);
		return ;
	}
	full_path = ft_strjoin(home_path, HIST_TMP_BASE);
	if (!full_path)
		ft_memory_error(sack);
	sack->history_fd = open(full_path, O_CREAT | O_RDWR, 0644);
	free(full_path);
}

void	ft_h_fill(t_minishell *sack)
{
	char	*line;
	char	*trimmed_line;

	while ((line = get_next_line(sack->history_fd)))
	{
		trimmed_line = ft_strtrim(line, "\n");
		if (!trimmed_line)
			ft_memory_error(sack);
		add_history(trimmed_line);
		free(line);
		free(trimmed_line);
	}
}

void	ft_add_history(char *str, t_minishell *sack)
{
	if (str && *str)
	{
		ft_putendl_fd(str, sack->history_fd);
		add_history(str);
	}
}
