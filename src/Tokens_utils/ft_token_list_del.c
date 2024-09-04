#include "../../includes/minishell.h"

void			token__list_del(t_token **token)
{
	t_token		*tmp;
	t_token		*tmpnext;

	tmp = *token;
	while (tmp)
	{
		tmpnext = tmp->next;
		token__del(&tmp);
		tmp = tmpnext;
	}
}