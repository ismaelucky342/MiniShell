/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:17:02 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:49 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Prints a syntax error message for a given token.
 *
 * This function outputs an error message to the standard error output,
 * indicating a syntax error near the specified token.
 *
 * @param token The token that caused the syntax error.
 */
static void	print_syntax_error(char *token)
{
	ft_putstr_fd("Minishell: syntax error near token '", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

/**
 * @brief Checks if a file redirection in the command string is valid.
 *
 * This function analyzes the string `str` starting from the index `*i`
 * to verify if the redirection operators are followed by valid file names.
 * If a syntax error is found, it prints an error message.
 *
 * @param str The command string being checked.
 * @param i A pointer to the index in the string to check for redirection.
 * @return OK if the redirection is valid, KO if a syntax error is found.
 */
int	ft_check_file(char *str, int *i)
{
	int	starting[2];

	starting[0] = *i;
	starting[1] = *i;
	if (!ft_strncmp("<<", &str[*i], 2) || !ft_strncmp(">>", &str[*i], 2))
		*i += 2;
	else if (!ft_strncmp("<", &str[*i], 1) || !ft_strncmp(">", &str[*i], 1))
		++(*i);
	while (str[*i] && ft_isspace(str[*i]))
		++(*i);
	starting[1] = *i;
	while (str[*i] && !ft_is_reserved_char(str[*i]) && !ft_isspace(str[*i]))
		++(*i);
	if (starting[1] != *i)
		return (OK);
	if (!ft_strncmp("<<", &str[starting[0]], 2) || !ft_strncmp(">>",
			&str[starting[0]], 2))
		print_syntax_error(&str[starting[0]]);
	else if (!ft_strncmp("<", &str[starting[0]], 1) || !ft_strncmp(">",
			&str[starting[0]], 1))
		print_syntax_error(&str[starting[0]]);
	return (KO);
}
/**
 * @brief Sets the terminal echo mode.
 *
 * This function enables or disables the echo mode of the terminal based on
 * the value of `val`. If `val` is non-zero, echo mode is enabled; if zero,
 * echo mode is disabled. The function uses the termios structure to change
 * the terminal settings.
 *
 * @param val A non-zero value to enable echo, or zero to disable it.
 * @return OK on success, KO on failure.
 */

int	ft_set_echo(int val)
{
	struct termios	settings;

	if (tcgetattr(STDIN_FILENO, &settings) == -1)
	{
		perror("tcgetattr");
		return (KO);
	}
	if (val)
		settings.c_lflag |= ECHO;
	else
		settings.c_lflag &= ~ECHO;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) == -1)
	{
		perror("tcsetattr");
		return (KO);
	}
	return (OK);
}
