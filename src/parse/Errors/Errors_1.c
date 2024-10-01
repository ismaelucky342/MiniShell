/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:17:02 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:00:09 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_syntax_error(char *token)
{
	ft_putstr_fd("Minishell: syntax error near token '", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

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
