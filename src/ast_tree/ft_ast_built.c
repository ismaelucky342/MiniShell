/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:00:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 12:06:27 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		init_tool(t_astb *tool, int sloc)
{
	ft_bzero(tool, sizeof(t_astb));
	if (!(tool->ast_tokenizer = ft_tokenizer_new(sloc)))
		return (ERROR);
	if ((tool->current_token = ft_tokenizer_get_next_token(tool->ast_tokenizer)) == NULL)
		return (ERROR);
	if (!tool->current_token || tool->current_token->type == TOKEN_END_TOKEN)
	{
		ft_tokenizer_delete(&tool->ast_tokenizer);
		return (EMPTY);
	}
	tool->previous_token = NULL;
	tool->tree_possition = NULL;
	tool->ast_tree= NULL;
	return (SUCCESS);
}

t_ast_node	*ast_builder(int sloc)
{
	t_astb		tool;
	int			ret;

	ret = init_tool(&tool, sloc);
	if (ret == EMPTY)
		return (ast_builder(sloc));
	if (ret != ERROR && process(&tool) != ERROR)
	{
		ft_tokenizer_delete(&tool.ast_tokenizer);
		return (tool.ast_tree);
	}
	ft_tokenizer_delete(&tool.ast_tokenizer);
	return (NULL);
}

