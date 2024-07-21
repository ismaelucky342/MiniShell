#include "../includes/minishell.h"

void	ft_free_tree_node(t_ast *ast_node)
{
	if (ast_node->value)
		ft_free_tree_val(ast_node->value);
	if (ast_node->redir_list)
		ft_free_rlist(ast_node->redir_list);
	free(ast_node);
}
