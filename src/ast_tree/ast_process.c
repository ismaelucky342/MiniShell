/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:03:16 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 16:04:50 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_call_next(t_astb *tool, t_ast_node **sep, t_mem_context *ctx)
{
	if (ft_token_issep(tool->current_token))
	{
		*sep = ft_node_new(SEPARATOR, ctx);
		if (*sep == NULL)
			return (ERROR);
		insert_node(tool, *sep);
		if (process(tool, ctx) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	process(t_astb *tool, t_mem_context *ctx)
{
	t_ast_node	*cmd;
	t_ast_node	*sep;

	if (tool->previous_token && (ft_token_istype(tool->previous_token,
				TOKEN_SEMICOLON) && ft_token_iseot(tool->current_token)))
		return (SUCCESS);
	if (ft_token_issep(tool->current_token)
		|| ft_token_iseot(tool->current_token))
		return (ft_tree_build_error(tool, BAD_TOKEN));
	cmd = ft_node_new(CMD, ctx);
	if (cmd == NULL)
		return (ERROR);
	while (ft_token_isword(tool->current_token)
		|| ft_token_isredir(tool->current_token))
	{
		if (ft_token_isredir(tool->current_token))
			continue ;
	}
	insert_node(tool, cmd);
	return (process_call_next(tool, &sep, ctx));
}
