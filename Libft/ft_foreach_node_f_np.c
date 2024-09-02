#include "libft.h"

void		ft_foreach_node_f_np(t_pnp **begin_list, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;
	t_pnp	*tmp2;

	tmp = *begin_list;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		f(tmp);
		tmp = tmp2;
	}
}
