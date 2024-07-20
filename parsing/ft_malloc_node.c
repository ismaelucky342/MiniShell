#include "minishell.h"

t_ast	*ft_malloc_node(int nb_element)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->value = calloc(nb_element + 1, sizeof(char **));
	node->redir_list = NULL;
	return (node);
}