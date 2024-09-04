#include "../../includes/minishell.h"

t_token			*token__new(t_token_type_key type, char *value, int pos)
{
	t_token		*new;

	new = mmalloc(sizeof(t_token));
	new->type = type;
	new->position_in_line = pos;
	new->value = value;
	new->length= 0;
	if (value)
		new->length= ft_strlen(value);
	return (new);
}
