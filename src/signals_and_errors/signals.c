/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:07:23 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 13:08:08 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

void	ft_signals(int signum)
{
	if (signum == SIGINT && (!g_is_exec || g_is_exec == 3))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_putendl_fd("\n^C", STDERR_FILENO);
		rl_redisplay();
		g_is_exec = 3;
	}
	else if (signum == SIGQUIT && g_is_exec == 1)
	{
		ft_putstr_fd("\nQuit (core dumped)", STDERR_FILENO);
		g_is_exec = 0;
	}
	else if (signum == SIGINT && g_is_exec == 1)
		g_is_exec = 0;
	else if (signum == SIGINT && g_is_exec == 2)
	{
		g_is_exec = 0;
		ft_putendl_fd("^C", STDERR_FILENO);
	}
}