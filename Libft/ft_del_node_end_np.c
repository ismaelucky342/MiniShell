#include "libft.h"

void		ft_del_node_end_np(t_pnp **begin_list, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp != *begin_list)
		tmp->prev->next = NULL;
	if (f)
		f(tmp);
	mfree((void **)&tmp);
}
