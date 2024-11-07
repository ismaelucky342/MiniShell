/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:03:17 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:27 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
extern int	g_exit;

/**
 * @brief Handles syntax errors by setting the appropriate environment variable.
 *
 * This function updates the environment variable `?` to indicate a syntax error.
 *
 * @param boogeyman Pointer to the main minishell structure.
 * @return Returns OK to indicate the error has been handled.
 */
static int handle_syntax_error(t_minishell *boogeyman)
{
	ft_env_build(boogeyman, "?=2");
	return (OK);
}

/**
 * @brief Checks for syntax issues in the command tree string.
 *
 * This function validates syntax by checking for unclosed quotes, mismatched
 * brackets, and invalid redirections. If any syntax error is found, it calls
 * `handle_syntax_error`.
 *
 * @param boogeyman Pointer to the main minishell structure.
 * @return Returns OK if a syntax error is found, KO otherwise.
 */
static int check_syntax(t_minishell *boogeyman)
{
	if (ft_check_quotes(boogeyman->cmd_tree->cmd_str))
		return (handle_syntax_error(boogeyman));
	if (ft_check_brackets(boogeyman->cmd_tree->cmd_str))
		return (handle_syntax_error(boogeyman));
	if (ft_check_fredirs(boogeyman->cmd_tree->cmd_str))
		return (handle_syntax_error(boogeyman));
	return (KO);
}

/**
 * @brief Checks and manages heredoc syntax and creation.
 *
 * This function checks heredoc syntax and attempts to create heredocs if no syntax
 * errors are found. It also updates the global `g_exit` status depending on the results.
 *
 * @param boogeyman Pointer to the main minishell structure.
 * @return Returns OK if heredocs are successfully checked and created, KO otherwise.
 */
int ft_check_heredoc(t_minishell *boogeyman)
{
	if (!check_syntax(boogeyman))
		return (OK);
	g_exit = 2;
	if (ft_create_heredocs(&boogeyman->cmd_tree->cmd_str))
	{
		g_exit = 0;
		return (handle_syntax_error(boogeyman));
	}
	if (!g_exit)
		return (ft_env_build(boogeyman, "?=130"), 0);
	g_exit = 0;
	return (KO);
}

