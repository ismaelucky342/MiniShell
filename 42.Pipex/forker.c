/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:33:08 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/05/22 11:38:00 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arr_freer(char **arr)
{
	int		i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i ++;
		}
		free(arr);
	}
}

void	fd_arr_closer(int *fds, int last)
{
	while (last >= 0)
	{
		close(fds[last]);
		last --;
	}
}

void	forker(int *fds, char **argv, char **env, t_index *index)
{
	int		pid;

	while (index->i < index->n_com)
	{
		pid = fork();
		if (pid < 0)
		{
			free(fds);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			execution(fds, argv[index->i +2], env, index);
		index->i ++;
		close(fds[(index->i * 2) - 1]);
		close(fds[(index->i * 2) - 2]);
	}
	while (index->i-- != 0)
		wait(NULL);
}
