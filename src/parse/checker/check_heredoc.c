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

static int	handle_syntax_error(t_minishell *boogeyman)
{
	ft_env_build(boogeyman, "?=2");
	return (OK);
}

static int	check_syntax(t_minishell *boogeyman)
{
	if (ft_check_quotes(boogeyman->cmd_tree->cmd_str))
		return (handle_syntax_error(boogeyman));
	if (ft_check_brackets(boogeyman->cmd_tree->cmd_str))
		return (handle_syntax_error(boogeyman));
	if (ft_check_fredirs(boogeyman->cmd_tree->cmd_str))
		return (handle_syntax_error(boogeyman));
	return (KO);
}

int	ft_check_heredoc(t_minishell *boogeyman)
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
