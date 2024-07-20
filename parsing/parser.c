#include "minishell.h"


t_ast	*ft_create_ast(t_token *token_list)
{
	t_ast	*ast_tree;
	t_ast	*node_holder;
	int		nb_element;

	ast_tree = NULL;
	node_holder = NULL;
	nb_element = 0;
	while (token_list)
	{
		nb_element = ft_count_element(token_list);
		node_holder = ft_create_ast_node(token_list, nb_element);
		if (!ast_tree)
			ast_tree = node_holder;
		else if (token_list->token_type == TOKEN_PIPE)
		{
			node_holder->left = ast_tree;
			ast_tree = node_holder;
		}
		else
			ast_tree->right = node_holder;
		while (nb_element--)
			token_list = token_list->next;
		node_holder = NULL;
	}
	return (ast_tree);
}