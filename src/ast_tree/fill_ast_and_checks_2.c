/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_and_checks_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:56:10 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 16:56:48 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_cmd_node(t_astb *tool, t_ast_node *node)
{
	tool->tree_possition->right = node;
	node->parent = tool->tree_possition;
	return (SUCCESS);
}

static int	handle_separator_node(t_astb *tool, t_ast_node *node)
{
	if (!node->separators)
		return (ft_tree_build_error(tool, BAD_TOKEN));
	if (ft_token_istype(node->separators, TOKEN_PIPE))
		find_for_node(tool, node,
			TYPE_LOGICAL_AND | TYPE_LOGICAL_OR | TYPE_SEMICOLON);
	else if (ft_token_istype(node->separators,
			TYPE_LOGICAL_AND | TYPE_LOGICAL_OR))
		find_for_node(tool, node, TOKEN_SEMICOLON);
	else if (ft_token_istype(node->separators, TOKEN_SEMICOLON))
		node_source(tool, node);
	tool->tree_possition = node;
	return (SUCCESS);
}

int	insert_node(t_astb *tool, t_ast_node *node)
{
	if (tool->ast_tree == NULL)
	{
		if (node->type == PIPE_DIV)
			return (ft_tree_build_error(tool, BAD_TOKEN));
		node_source(tool, node);
	}
	else
	{
		if (node->type == CMD)
			return (handle_cmd_node(tool, node));
		else if (node->type == PIPE_DIV)
			return (handle_separator_node(tool, node));
	}
	return (SUCCESS);
}
