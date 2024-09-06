/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:00:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 16:15:08 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/AST.h"
#include "../../includes/minishell.h"

int	init_tool(t_astb *tool, int sloc)
{
	ft_bzero(tool, sizeof(t_astb));
	tool->ast_tokenizer = ft_tokenizer_new(sloc);
	if (tool->ast_tokenizer == NULL)
		return (ERROR);
	tool->current_token = ft_tokenizer_get_next_token(tool->ast_tokenizer);
	if (tool->current_token == NULL)
	{
		ft_tokenizer_delete(&tool->ast_tokenizer);
		return (ERROR);
	}
	if (tool->current_token->type == TOKEN_END_TOKEN)
	{
		ft_tokenizer_delete(&tool->ast_tokenizer);
		return (EMPTY);
	}
	tool->previous_token = NULL;
	tool->tree_possition = NULL;
	tool->ast_tree = NULL;
	return (SUCCESS);
}

void	init_mem_context(t_mem_context *ctx)
{
	if (ctx)
	{
		ctx->allocated_list = NULL;
	}
}

t_ast_node	*ast_builder(int sloc, t_mem_context *ctx)
{
	t_astb			tool;
	int				ret;
	t_mem_context	ctx;

	init_mem_context(&ctx);
	ret = init_tool(&tool, sloc);
	if (ret == EMPTY)
	{
		ft_tokenizer_delete(&tool.ast_tokenizer);
		return (ast_builder(sloc, &ctx));
	}
	if (ret != ERROR && process(&tool, &ctx) != ERROR)
	{
		ft_tokenizer_delete(&tool.ast_tokenizer);
		return (tool.ast_tree);
	}
	ft_tokenizer_delete(&tool.ast_tokenizer);
	return (NULL);
}
