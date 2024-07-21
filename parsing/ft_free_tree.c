
#include "../includes/minishell.h"

void	ft_free_tree(t_ast *ast_tree)
{
	t_ast	*node_holder;

	while (ast_tree)
	{
		if (ast_tree->right)
			ft_free_tree_node(ast_tree->right);
		node_holder = ast_tree;
		ast_tree = ast_tree->left;
		ft_free_tree_node(node_holder);
	}
	return ;
}
