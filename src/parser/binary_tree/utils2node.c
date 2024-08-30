#include "minishell.h"

t_ast_node	*new_node(void)
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

t_ast_node	*new_redir_node(void)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = REDIR;
	node->value = NULL;  
	node->children = NULL;
	node->children_count = 0;
	return (node);
}

t_token	*delete_parens(t_token *token_first)
{
	t_token	*token_last;

	token_last = skip_parens(token_first, 1);
	if (token_last->next)
	{
		print_syntax_err(token_last);
		return (NULL);
	}
	token_last = token_last->prev;
	token_delete(&token_last->next);
	token_delete(&token_first);
	if (!token_first)
	{
		print_syntax_err(NULL);
		return (NULL);
	}
	return (token_last);
}
