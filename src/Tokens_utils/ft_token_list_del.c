#include "../../includes/minishell.h"

void			ft_token_list_del(t_token **token)
{
	t_token		*tmp;
	t_token		*tmpnext;

	tmp = *token;
	while (tmp)
	{
		tmpnext = tmp->next;
		ft_token_del(&tmp);
		tmp = tmpnext;
	}
}