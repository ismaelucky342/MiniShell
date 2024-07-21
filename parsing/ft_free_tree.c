
#include "../includes/minishell.h"

void	ft_free_redir_list(t_redir *redir_list)
{
	t_redir	*ptr;

	while (redir_list)
	{
		ptr = redir_list;
		redir_list = redir_list->next;
		free(ptr->value);
		free(ptr);
	}
}

void	ft_free_ast_value(char **value)
{
	char	**holder;

	holder = value;
	while (*value)
	{
		free(*value);
		value++;
	}
	free(holder);
}

void	ft_free_ast_node(t_ast *ast_node)
{
	if (ast_node->value)
		ft_free_ast_value(ast_node->value);
	if (ast_node->redir_list)
		ft_free_redir_list(ast_node->redir_list);
	free(ast_node);
}

void	ft_free_ast(t_ast *ast_tree)
{
	t_ast	*node_holder;

	while (ast_tree)
	{
		if (ast_tree->right)
			ft_free_ast_node(ast_tree->right);
		node_holder = ast_tree;
		ast_tree = ast_tree->left;
		ft_free_ast_node(node_holder);
	}
	return ;
}
