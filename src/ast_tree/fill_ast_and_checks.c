# include "../../includes/minishell.h"

int		coincidence(t_astb *tool, t_token_type_key type)
{
	if (!token__istype(tool->current_token, type))
		return (astb_error(tool, BAD_TOKEN));
	tool->previous_token = tool->current_token;
	if ((tool->current_token = lexer__get_next_token(tool->ast_lexer)) == NULL)
		return (ERROR);
	return (SUCCESS);
}

int		insert_node(t_astb *tool, t_token **tokendest, t_ast_tokens type)
{
	if (type == ASTREDIR &&
		coincidence(tool, token__isredir(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == ASTWORDS &&
		coincidence(tool, token__isword(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == ASTSEPARATOR &&
		coincidence(tool, token__issep(tool->current_token)) == ERROR)
		return (ERROR);
	ft_add_node_end_np((t_pnp **)tokendest, (t_pnp *)tool->previous_token);
	return (SUCCESS);
}

void	node_source(t_astb *tool, t_ast_node *node)
{
	node->left = tool->ast_tree;
	node->right = NULL;
	node->Father = NULL;
	if (tool->ast_tree )
	{
		
		tool->ast_tree->Father = node;
		tool->tree_possition = node;
	}
	tool->ast_tree = node;
}

void	find_for_node(t_astb *tool, t_ast_node *node, t_token_type_key type)
{
	while (tool->tree_possition && (tool->tree_possition->type == CMD ||
		!token__istype(tool->tree_possition->separators, type)))
		tool->tree_possition = tool->tree_possition->Father;
	if (!tool->tree_possition)
		set_root_to_node(tool, node);
	else
	{
		node->left = tool->tree_possition->right;
		node->left->Father = node;
		node->right = NULL;
		node->Father = tool->tree_possition;
		tool->tree_possition->right = node;
	}
}

int		insert_into_ast(t_astb *tool, t_ast_node *node)
{
	if (tool->ast_tree == NULL)
	{
		if (node->type == SEPARATOR)
			return (astb_error(tool, BAD_TOKEN));
		set_root_to_node(tool, node);
	}
	else
	{
		if (node->type == CMD && (tool->tree_possition->right = node))
			node->Father = tool->tree_possition;
		else if (node->type == SEPARATOR)
		{
			if (!node->separators)
				return (astb_error(tool, BAD_TOKEN));
			if (token__istype(node->separators, TOKEN_PIPE))
				search_place_node(tool, node, TYPE_LOGICAL_AND | TYPE_LOGICAL_OR | TYPE_SEMICOLON);
			else if (token__istype(node->separators, TYPE_LOGICAL_AND | TYPE_LOGICAL_OR))
				search_place_node(tool, node, TOKEN_SEMICOLON);
			else if (token__istype(node->separators, TOKEN_SEMICOLON))
				set_root_to_node(tool, node);
			tool->tree_possition = node;
		}
	}
	return (SUCCESS);
}