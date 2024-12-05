/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:58:58 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/05 12:45:03 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

/**
 * @brief Checks the syntax of the heredoc in the given minishell instance.
 *
 * This function performs several syntax checks on the command string of the
 * minishell instance's command tree. It checks for quotes, brackets, and
 * redirections. If any of these checks fail, it sets an environment variable
 * to indicate an error and returns 0. If all checks pass, it attempts to
 * create heredocs. If this creation fails, it sets an environment variable
 * to indicate an error and returns 0. If the execution flag is not set, it
 * sets an environment variable to indicate a different error and returns 0.
 * Finally, if all operations succeed, it returns 1.
 *
 * @param boogeyman A pointer to the minishell instance.
 * @return int 1 if the syntax is correct and heredocs are created successfully,
 *             0 otherwise.
 */
int	ft_check_syntax_heredoc(t_minishell *boogeyman)
{
	if (ft_check_quotes(boogeyman->cmd_tree->cmd_str))
		return (ft_add_to_env(boogeyman, "?=2"), 0);
	if (ft_check_brackets(boogeyman->cmd_tree->cmd_str))
		return (ft_add_to_env(boogeyman, "?=2"), 0);
	if (ft_check_fredirs(boogeyman->cmd_tree->cmd_str))
		return (ft_add_to_env(boogeyman, "?=2"), 0);
	g_is_exec = 2;
	if (ft_create_heredocs(&boogeyman->cmd_tree->cmd_str))
		return (g_is_exec = 0, ft_add_to_env(boogeyman, "?=2"), 0);
	if (!g_is_exec)
		return (ft_add_to_env(boogeyman, "?=130"), 0);
	g_is_exec = 0;
	return (1);
}