/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:13:06 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/07/17 12:13:07 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_fds(int n_com, char **argv, int *fds)
{
	int		tmp;
	int		i;

	fds[0] = open(argv[1], O_RDONLY);
	i = 0;
	while (i < n_com - 1)
	{
		if (pipe(&fds[(i * 2) + 1]))
			return (fd_arr_closer(fds, (i * 2) + 2), 1);
		tmp = fds[(i * 2) + 2];
		fds[(i * 2) + 2] = fds[(i * 2) + 1];
		fds[(i++ *2) + 1] = tmp;
	}
	fds[(i * 2) + 1] = open(argv[n_com + 2], 0100 | 01 | 01000, 0644);
	return (0);
}

int	pipahx(int argc, char **argv, char **env)
{
	int			*fds;
	t_index		index;

	if (argc < 5)
		return (ft_putstr_fd(ARGS_ERR_1, 2), ft_putstr_fd(ARGS_ERR_2, 2), 1);
	index.i = 0;
	index.n_com = argc - 3;
	index.total = index.n_com - 1;
	index.fd_count = index.n_com * 2;
	index.bonus = 1;
	index.in = argv[1];
	index.out = argv[argc - 1];
	fds = ft_calloc(index.n_com * 2, sizeof(int));
	if (!fds)
		return (ft_putendl_fd("Malloc error.", 2), 1);
	init_fds(index.n_com, argv, fds);
	forker(fds, argv, env, &index);
	free(fds);
	return (0);
}
