/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:03:16 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 12:22:22 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	proc_next(t_astb *tool, t_ast_node **sep)
{
	if (ft_token_issep(tool->current_token))
	{
		*sep = ft_node_new(PIPE_DIV);
		if (*sep == NULL)
			return (ERROR);
		insert_node(tool, *sep);
		if (process(tool) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	process(t_astb *tool)
{
	t_ast_node	*cmd;
	t_ast_node	*sep;

	if (tool->previous_token && (ft_token_istype(tool->previous_token,
				TOKEN_SEMICOLON) && ft_token_iseot(tool->current_token)))
		return (SUCCESS);
	if (ft_token_issep(tool->current_token)
		|| ft_token_iseot(tool->current_token))
		return (ft_tree_build_error(tool, BAD_TOKEN));
	cmd = ft_node_new(CMD);
	if (cmd == NULL)
		return (ERROR);
	while (ft_token_isword(tool->current_token)
		|| ft_token_isredir(tool->current_token))
	{
		if (ft_token_isredir(tool->current_token))
			continue ;
	}
	insert_node(tool, cmd);
	return (proc_next(tool, &sep));
}
