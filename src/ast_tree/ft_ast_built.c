/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:00:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 10:37:23 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/AST.h"
#include "../../includes/minishell.h"

static void	init_mem_context(t_mem_context *ctx)
{
	if (ctx)
	{
		ctx->allocated_list = NULL;
	}
}

int	init_tool(t_astb *tool, int sloc, t_mem_context *ctx,
		t_hashtable *env_hashtable)
{
	ft_bzero(tool, sizeof(t_astb));
	tool->ast_tokenizer = ft_tokenizer_new(sloc, ctx, env_hashtable);
	if (tool->ast_tokenizer == NULL)
		return (ERROR);
	tool->current_token = ft_tokenizer_get_next_token(tool->ast_tokenizer, ctx);
	if (tool->current_token == NULL)
	{
		ft_tokenizer_delete(&tool->ast_tokenizer, ctx);
		return (ERROR);
	}
	if (tool->current_token->type == TOKEN_END_TOKEN)
	{
		ft_tokenizer_delete(&tool->ast_tokenizer, ctx);
		return (EMPTY);
	}
	tool->previous_token = NULL;
	tool->tree_possition = NULL;
	tool->ast_tree = NULL;
	return (SUCCESS);
}

t_ast_node	*ast_builder(int sloc, t_mem_context *ctx,
		t_hashtable *env_hashtable)
{
	t_astb	tool;
	int		ret;

	init_mem_context(ctx);
	ret = init_tool(&tool, sloc, ctx, env_hashtable);
	if (ret == EMPTY)
	{
		ft_tokenizer_delete(&tool.ast_tokenizer, ctx);
		return (ast_builder(sloc, ctx, env_hashtable));
	}
	if (ret != ERROR && process(&tool, ctx) != ERROR)
	{
		ft_tokenizer_delete(&tool.ast_tokenizer, ctx);
		return (tool.ast_tree);
	}
	ft_tokenizer_delete(&tool.ast_tokenizer, ctx);
	return (NULL);
}
