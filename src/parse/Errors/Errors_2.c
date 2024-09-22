/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:09:30 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:00:28 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_error(char *msg)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

int	ft_set_signal(int val)
{
	struct termios	settings;

	if (tcgetattr(STDIN_FILENO, &settings) == -1)
	{
		perror("tcgetattr");
		return (1);
	}
	if (val)
		settings.c_lflag |= ECHOCTL;
	else
		settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) == -1)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}

void	ft_memory_error(t_minishell *sack)
{
	print_error("memory error");
	ft_exit_msg(2, sack, 0);
}

void	ft_tmp(char **tmp, int *shllvl)
{
	ft_putstr_fd("Minishell: warning: shell level (", STDERR_FILENO);
	*tmp = ft_itoa(*shllvl);
	ft_putstr_fd(*tmp, STDERR_FILENO);
	free(*tmp);
	*tmp = NULL;
	ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
	*shllvl = 1;
}