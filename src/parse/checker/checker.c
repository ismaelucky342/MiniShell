/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:31:39 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/12 11:27:32 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit;

/**
 * @brief Checks if quotes in the string are balanced.
 *
 * This function iterates through `str` to ensure all single and double quotes
 * are closed properly. If an unbalanced quote is detected, it displays an error message.
 *
 * @param str The string to check for balanced quotes.
 * @return OK if quotes are balanced, KO if unbalanced quotes are found.
 */
int ft_check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			skip_to_delimiter(str, &i, str[i]);
			if (!str[i])
			{
				ft_quote_error();
				return (KO);
			}
			else
				++i;
		}
		else
			++i;
	}
	return (OK);
}

/**
 * @brief Checks if parentheses in the string are balanced.
 *
 * This function checks for balanced opening and closing parentheses in `str`.
 * If an imbalance is detected, it displays an error message.
 *
 * @param str The string to check for balanced parentheses.
 * @return OK if parentheses are balanced, KO if unbalanced parentheses are found.
 */
int ft_check_brackets(char *str)
{
	int	opening;
	int	closing;
	int	i;

	opening = 0;
	closing = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_to_delimiter(str, &i, str[i]);
		else if (str[i] == '(')
			++opening;
		else if (str[i] == ')')
			++closing;
		if (str[i])
			++i;
	}
	if (opening != closing)
	{
		ft_bracket_error();
		return (KO);
	}
	return (OK);
}

/**
 * @brief Creates heredoc files as specified in the command string.
 *
 * The function parses `str` for heredoc operators (`<<`) and creates
 * corresponding heredoc files if needed. Each heredoc file is unlinked if the
 * global `g_exit` indicates a successful exit.
 *
 * @param str A pointer to the command string being parsed.
 * @return OK on success, KO if heredoc creation fails.
 */
int ft_create_heredocs(char **str)
{
	int		i;
	char	*f_name;

	i = 0;
	f_name = NULL;
	while ((*str)[i] && g_exit)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			skip_to_delimiter(*str, &i, (*str)[i]);
		if (!ft_strncmp("<<", &(*str)[i], 2))
			if (ft_heredoc(str, &i, &f_name))
				return (KO);
		waitpid(-1, NULL, 0);
		if (f_name)
		{
			if (!g_exit)
				unlink(f_name);
			free(f_name);
			f_name = NULL;
		}
		if ((*str)[i])
			++i;
	}
	return (OK);
}

/**
 * @brief Checks for valid file redirections in the string.
 *
 * This function searches `str` for redirection operators (`<`, `<<`, `>`, `>>`)
 * and verifies that each operator is followed by a valid file name.
 *
 * @param str The command string to check for valid file redirections.
 * @return OK if redirections are valid, or the error code if invalid.
 */
int ft_check_fredirs(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i] && !check)
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_to_delimiter(str, &i, str[i]);
		else if (!ft_strncmp("<<", &str[i], 2) || !ft_strncmp("<", &str[i], 1)
			|| !ft_strncmp(">>", &str[i], 2) || !ft_strncmp(">", &str[i], 1))
		{
			check = ft_check_file(str, &i);
		}
		else
			++i;
		if (check)
			return (check);
	}
	return (OK);
}
