#include "../../includes/minishell.h"

t_token			*ft_token_copy(t_token *token)
{
	t_token		*new;

	new = mmalloc(sizeof(t_token));
	new->type = token->type;
	new->position_in_line = token->position_in_line;
	new->value = ft_strdup(token->value);
	new->length = token->length;
	return (new);
}