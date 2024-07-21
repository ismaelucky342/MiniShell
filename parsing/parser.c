
#include "../includes/minishell.h"

int	ft_count_element(t_token *token_list)
{
	int		count;
	t_token	*ptr;

	ptr = token_list;
	count = 0;
	if (ptr->token_type == TOKEN_PIPE)
		count++;
	while (ptr && ptr->token_type != TOKEN_PIPE)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

int	ft_is_redir(int token_type)
{
	if (token_type == TOKEN_GREATER || token_type == TOKEN_GREATGREATER || \
		token_type == TOKEN_LESSER || token_type == TOKEN_LESSLESSER)
		return (1);
	return (0);
}

t_ast	*ft_create_tree(t_token *token_list)
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
		node_holder = ft_create_tree_node(token_list, nb_element);
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
