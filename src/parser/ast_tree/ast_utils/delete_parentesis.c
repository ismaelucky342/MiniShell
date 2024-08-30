#include "minishell.h"

t_token	*delete_parentesiss(t_token *token_first)
{
	t_token	*token_last;

	token_last = skip_parentesiss(token_first, 1);
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
