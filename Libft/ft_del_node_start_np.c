#include "libft.h"

void		ft_del_node_start_np(t_pnp **begin_list, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	*begin_list = (*begin_list)->next;
	(*begin_list)->next->prev = NULL;
	if (f)
		f(tmp);
	mfree((void **)&tmp);
}
