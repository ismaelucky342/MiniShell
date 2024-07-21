
#include "../includes/minishell.h"

void	ft_free_rlist(t_redir *redir_list)
{
	t_redir	*ptr;

	while (redir_list)
	{
		ptr = redir_list;
		redir_list = redir_list->next;
		free(ptr->value);
		free(ptr);
	}
}