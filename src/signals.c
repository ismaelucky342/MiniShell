/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:01:12 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 13:34:12 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_signal_context	g_signals;

void	init_signal_context(t_signal_context *context)
{
	context->exit_status = 0;
	context->reset_flag = 0;
	context->env_hashtable = NULL;
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		g_signals.reset_flag = 1;
		g_signals.exit_status = 130;
		print_prompt(0, g_signals.env_hashtable);
	}
	else if (signo == SIGTSTP)
	{
		printf("\b\b  \b\b");
	}
}
