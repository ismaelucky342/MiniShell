/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:03:17 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:26:16 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit;

static int	handle_syntax_error(t_minishell *sack)
{
	ft_env_build(sack, "?=2");
	return (OK);
}

static int	check_syntax(t_minishell *sack)
{
	if (ft_check_quotes(sack->cmd_tree->cmd_str))
		return (handle_syntax_error(sack));
	if (ft_check_brackets(sack->cmd_tree->cmd_str))
		return (handle_syntax_error(sack));
	if (ft_check_fredirs(sack->cmd_tree->cmd_str))
		return (handle_syntax_error(sack));
	return (KO);
}

int	ft_check_heredoc(t_minishell *sack)
{
	if (!check_syntax(sack))
		return (OK);
	g_exit = 2;
	if (ft_create_heredocs(&sack->cmd_tree->cmd_str))
	{
		g_exit = 0;
		return (handle_syntax_error(sack));
	}
	if (!g_exit)
		return (ft_env_build(sack, "?=130"), 0);
	g_exit = 0;
	return (KO);
}
