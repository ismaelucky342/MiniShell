#include "minishell.h"

t_ast_node	*ft_ast_new_node(void)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = ERROR;  
	node->value = NULL;
	node->children = NULL;
	node->children_count = 0;
	return (node);
}