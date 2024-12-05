/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:28:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 13:27:09 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

/**
 * ft_file_name_c - Checks the syntax of a file name in a shell command.
 * @str: The input string containing the shell command.
 * @i: A pointer to the current index in the input string.
 *
 * This function checks if the current position in the input string
 * (pointed to by @i) contains a valid file name following a redirection
 * operator ('<', '>', '<<', '>>'). It skips over any whitespace and
 * verifies that the file name does not contain reserved characters or
 * additional whitespace.
 *
 * Return: 0 if a valid file name is found, 1 if there is a syntax error.
 *
 * If a syntax error is detected, an error message is printed to STDERR.
 */
int	ft_file_name_checker(char *str, int *i)
{
	int	starting[2];

	starting[0] = *i;
	if (!ft_strncmp("<<", &str[*i], 2) || !ft_strncmp(">>", &str[*i], 2))
		*i += 2;
	else if (!ft_strncmp("<", &str[*i], 1) || !ft_strncmp(">", &str[*i], 1))
		++(*i);
	while (str[*i] && ft_isspace(str[*i]))
		++(*i);
	starting[1] = *i;
	while (str[*i] && !ft_isreserved(str[*i]) && !ft_isspace(str[*i]))
		++(*i);
	if (starting[1] != *i)
		return (0);
	ft_putstr_fd("MiniShell: syntax error near token '", STDERR_FILENO);
	if (!ft_strncmp("<<", &str[starting[0]], 2)
		|| !ft_strncmp(">>", &str[starting[0]], 2))
		(void) (write(STDERR_FILENO, &str[starting[0]], 2) + 1);
	else if (!ft_strncmp("<", &str[starting[0]], 1)
		|| !ft_strncmp(">", &str[starting[0]], 1))
		(void) (write(STDERR_FILENO, &str[starting[0]], 1) + 1);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}

/**
 * Checks for unmatching quotes in the given string.
 *
 * @param str The string to be checked for quotes.
 * @return 1 if there is an unmatching number of quotes, 0 otherwise.
 */
int	ft_check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			state_quote_delimiter(str, &i, str[i]);
			if (!str[i])
			{
				ft_print_syntax_error("unmatching number of quotes");
				return (1);
			}
			else
				++i;
		}
		else
			++i;
	}
	return (0);
}

/**
 * Checks for unmatching brackets in the given string.
 *
 * @param str The string to be checked for brackets.
 * @return 1 if there is an unmatching number of brackets, 0 otherwise.
 */
int	ft_check_brackets(char *str)
{
	int	opening;
	int	closing;
	int	i;

	i = 0;
	opening = 0;
	closing = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			state_quote_delimiter(str, &i, str[i]);
		else if (str[i] == '(')
			++opening;
		else if (str[i] == ')')
			++closing;
		if (str[i])
			++i;
	}
	if (closing != opening)
	{
		ft_print_syntax_error("unmatching number of brackets");
		return (1);
	}
	return (0);
}

/**
 * Checks for file redirections in the given string.
 *
 * @param str The string to be checked for file redirections.
 * @return 1 if there is an error with file redirections, 0 otherwise.
 */
int	ft_check_fredirs(char *str)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (str[i] && !check)
	{
		if (str[i] == '\'' || str[i] == '"')
			state_quote_delimiter(str, &i, str[i]);
		else if (!ft_strncmp("<<", &str[i], 2) || !ft_strncmp("<", &str[i], 1)
			|| !ft_strncmp(">>", &str[i], 2) || !ft_strncmp(">", &str[i], 1))
			check = ft_file_name_checker(str, &i);
		else
			++i;
		if (check)
			return (check);
	}
	return (0);
}
