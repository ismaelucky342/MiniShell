# include "../../includes/minishell.h"

int		coincidence(t_astb *tool, t_token_type_key type)
{
	if (!ft_token_istype(tool->current_token, type))
		return (ft_tree_build_error(tool, BAD_TOKEN));
	tool->previous_token = tool->current_token;
	if ((tool->current_token = ft_tokenizer_get_next_token(tool->ast_tokenizer)) == NULL)
		return (ERROR);
	return (SUCCESS);
}

int		insert_into_node(t_astb *tool, t_token **tokendest, t_ast_tokens type)
{
	if (type == ASTREDIR &&
		coincidence(tool, ft_token_isword(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == ASTWORDS &&
		coincidence(tool, ft_token_isword(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == ASTSEPARATOR &&
		coincidence(tool, ft_token_issep(tool->current_token)) == ERROR)
		return (ERROR);
	ft_add_node_end_np((t_pnp **)tokendest, (t_pnp *)tool->previous_token);
	return (SUCCESS);
}

void	node_source(t_astb *tool, t_ast_node *node)
{
	node->left = tool->ast_tree;
	node->right = NULL;
	node->father = NULL;
	if (tool->ast_tree )
	{
		
		tool->ast_tree->father = node;
		tool->tree_possition = node;
	}
	tool->ast_tree = node;
}

void	find_for_node(t_astb *tool, t_ast_node *node, t_token_type_key type)
{
	while (tool->tree_possition && (tool->tree_possition->type == CMD ||
		!ft_token_istype(tool->tree_possition->separators, type)))
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

int		insert_node(t_astb *tool, t_ast_node *node)
{
	if (tool->ast_tree == NULL)
	{
		if (node->type == SEPARATOR)
			return (ft_tree_build_error(tool, BAD_TOKEN));
		node_source(tool, node);
	}
	else
	{
		if (node->type == CMD && (tool->tree_possition->right = node))
			node->father = tool->tree_possition;
		else if (node->type == SEPARATOR)
		{
			if (!node->separators)
				return (ft_tree_build_error(tool, BAD_TOKEN));
			if (ft_token_istype(node->separators, TOKEN_PIPE))
				find_for_node(tool, node, TYPE_LOGICAL_AND | TYPE_LOGICAL_OR | TYPE_SEMICOLON);
			else if (ft_token_istype(node->separators, TYPE_LOGICAL_AND | TYPE_LOGICAL_OR))
				find_for_node(tool, node, TOKEN_SEMICOLON);
			else if (ft_token_istype(node->separators, TOKEN_SEMICOLON))
				node_source(tool, node);
			tool->tree_possition = node;
		}
	}
	return (SUCCESS);
}