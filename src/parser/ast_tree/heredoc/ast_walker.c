int	ast_walker(t_ast_node *node, t_node_type type)
{
	if (type == CMD)
		return (cmd_handle((t_cmd *)node->value));
	else if (type == REDIR)
		return (redir_handle((t_redir *)node->value));
	else if (type == PIPE || type == AND || type == OR)
	{
		if (node->children_count > 0 && node->children[0])
		{
			if (ast_walker(node->children[0], node->children[0]->type) == -1)
				return (-1);
		}
		if (node->children_count > 1 && node->children[1])
			return (ast_walker(node->children[1], node->children[1]->type));
	}
	return (-1);
}