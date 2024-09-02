#include "libft.h"

void		ft_add_node_start_np(t_pnp **begin_list, t_pnp *new)
{
	new->next = *begin_list;
	new->prev = NULL;
	if (*begin_list)
		(*begin_list)->prev = new;
	*begin_list = new;
}
