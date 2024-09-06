/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_and_checks_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:00:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 12:58:39 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	coincidence(t_astb *tool, t_token_type_key type)
{
	if (!ft_token_istype(tool->current_token, type))
		return (ft_tree_build_error(tool, BAD_TOKEN));
	tool->previous_token = tool->current_token;
	tool->current_token = ft_tokenizer_get_next_token(tool->ast_tokenizer);
	if (tool->current_token == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	insert_into_node(t_astb *tool, t_token **tokendest, t_ast_tokens type)
{
	if (type == ASTREDIR && coincidence(tool,
			ft_token_isword(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == ASTWORDS && coincidence(tool,
			ft_token_isword(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == ASTSEPARATOR && coincidence(tool,
			ft_token_issep(tool->current_token)) == ERROR)
		return (ERROR);
	ft_add_node_end_np((t_pnp **)tokendest, (t_pnp *)tool->previous_token);
	return (SUCCESS);
}

void	node_source(t_astb *tool, t_ast_node *node)
{
	node->left = tool->ast_tree;
	node->right = NULL;
	node->father = NULL;
	if (tool->ast_tree)
	{
		tool->ast_tree->father = node;
		tool->tree_possition = node;
	}
	tool->ast_tree = node;
}

void	find_for_node(t_astb *tool, t_ast_node *node, t_token_type_key type)
{
	while (tool->tree_possition && (tool->tree_possition->type == CMD
			|| !ft_token_istype(tool->tree_possition->separators, type)))
		tool->tree_possition = tool->tree_possition->father;
	if (!tool->tree_possition)
		node_source(tool, node);
	else
	{
		node->left = tool->tree_possition->right;
		node->left->father = node;
		node->right = NULL;
		node->father = tool->tree_possition;
		tool->tree_possition->right = node;
	}
}
