/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:59:21 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:25:21 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit;

void	ft_sig_handler(int signum)
{
	if (signum == SIGINT && (!g_exit || g_exit == 3))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_putendl_fd("\n^C", STDERR_FILENO);
		rl_redisplay();
		g_exit = 3;
	}
	else if (signum == SIGQUIT && g_exit == 1)
	{
		ft_putstr_fd("\nQuit (core dumped)", STDERR_FILENO);
		g_exit = 0;
	}
	else if (signum == SIGINT && g_exit == 1)
		g_exit = 0;
	else if (signum == SIGINT && g_exit == 2)
	{
		g_exit = 0;
		ft_putendl_fd("^C", STDERR_FILENO);
	}
}

void	ft_set_signal_handlers(void)
{
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
}
