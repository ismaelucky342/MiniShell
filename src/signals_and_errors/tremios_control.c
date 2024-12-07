/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tremios_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:52:06 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 16:28:05 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Sets the terminal's echo control flag based on the given value.
 *
 * This function modifies the terminal's local flags to either enable or disable
 * the ECHOCTL flag, which controls whether control characters are echoed as
 * ^X (where X is the corresponding character) or not echoed at all.
 *
 * @param val An integer value indicating whether to enable or disable ECHOCTL.
 *            If val is non-zero, ECHOCTL is enabled. If val is zero,
	ECHOCTL is disabled.
 * @return Returns 0 on success, or 1 if an error occurs.
 */
int	ft_set_signal_print(int val)
{
	struct termios	settings;

	if (!isatty(STDIN_FILENO))
		return (0);
	if (!isatty(STDIN_FILENO) || tcgetattr(STDIN_FILENO, &settings) < 0)
	{
		perror("tcgetattr");
		return (1);
	}
	if (val)
		settings.c_lflag |= ECHOCTL;
	else
		settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) < 0)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}

/**
 * @brief Sets the echo flag for terminal input.
 *
 * This function modifies the terminal settings to enable or disable the echo
 * flag,
	which controls whether input characters are echoed back to the terminal.
 *
 * @param val If non-zero, the echo flag is enabled. If zero,
	the echo flag is disabled.
 * @return Returns 0 on success, or 1 on failure.
 */
int	ft_set_echo(int val)
{
	struct termios	settings;

	if (!isatty(STDIN_FILENO) || tcgetattr(STDIN_FILENO, &settings) == -1)
	{
		perror("tcgetattr");
		return (1);
	}
	if (val)
		settings.c_lflag |= ECHO;
	else
		settings.c_lflag &= ~ECHO;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) == -1)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}
