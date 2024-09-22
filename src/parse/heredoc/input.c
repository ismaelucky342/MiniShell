/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:54 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit;

static char	*join_with_space(char *str1, char *str2)
{
	char	*joined;

	joined = ft_strjoin(str1, " ");
	free(str1);
	return (ft_strjoin(joined, str2));
}

void	new_string(char **str, int j, char *tmp, char *tmp2)
{
	tmp = ft_strjoin(tmp2, " ");
	free(tmp2);
	tmp2 = ft_substr(*str, j, SIZE_T_MAX);
	free(*str);
	*str = join_with_space(tmp, tmp2);
	free(tmp);
	free(tmp2);
}

void	heredoc_input(char **line, char *prompt, char *delim, int *fd)
{
	while (*line && ft_strncmp(*line, delim, ft_strlen(delim) + 1))
	{
		ft_putendl_fd(*line, *fd);
		free(*line);
		*line = readline(prompt);
	}
	free(*line);
	*line = NULL;
}
