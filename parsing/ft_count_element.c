#include "minishell.h"

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