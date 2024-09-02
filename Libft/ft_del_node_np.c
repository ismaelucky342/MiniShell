#include "libft.h"

void		ft_del_node_np(t_pnp **begin_list, t_pnp *del,
	void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	if (tmp == del)
	{
		*begin_list = (*begin_list)->next;
		if (*begin_list)
			(*begin_list)->prev = NULL;
	}
	else
	{
		while (tmp->next != del)
			tmp = tmp->next;
		if (tmp->next == NULL)
			return ;
		tmp->next = del->next;
		tmp->next->prev = tmp;
	}
	if (f)
		f(del);
	mfree((void **)&del);
}
