/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:22:19 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 15:22:21 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_signal;

void	exec_handler(int signal)
{
	g_signal = 1;

	if (signal == SIGINT)
		write(STDIN_FILENO, "\n", 1);
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}
