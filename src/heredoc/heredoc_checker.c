/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:58:58 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/07 20:46:26 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

/**
 * @brief Checks the syntax of the heredoc in the given minishell instance.
 *
 * This function performs several syntax checks on the command string of the
 * minishell instance's command tree. It checks for quotes, brackets, and
 * redirections. If any of these checks fail, it sets an env variable
 * to indicate an error and returns 0. If all checks pass, it attempts to
 * create heredocs. If this creation fails, it sets an env variable
 * to indicate an error and returns 0. If the execution flag is not set, it
 * sets an env variable to indicate a different error and returns 0.
 * Finally, if all operations succeed, it returns 1.
 *
 * @param boogeyman A pointer to the minishell instance.
 * @return int 1 if the syntax is correct and heredocs are created successfully,
 *             0 otherwise.
 */
int	ft_check_syntax_heredoc(t_mini *boogeyman)
{
	if (ft_check_quotes(boogeyman->cmd_tree->cmd_str))
		return (boogeyman->rvalue = 2, 0);
	if (ft_check_brackets(boogeyman->cmd_tree->cmd_str))
		return (boogeyman->rvalue = 2, 0);
	if (ft_check_fredirs(boogeyman->cmd_tree->cmd_str))
		return (boogeyman->rvalue = 2, 0);
	g_is_exec = 2;
	if (ft_create_heredocs(&boogeyman->cmd_tree->cmd_str))
		return (g_is_exec = 0, boogeyman->rvalue = 2, 0);
	if (!g_is_exec)
		return (boogeyman->rvalue = 130, 0);
	g_is_exec = 0;
	return (1);
}
