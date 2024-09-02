#include "libft.h"

void		ft_add_node_f_prevto_np(
	t_pnp **begin_list, t_pnp *new, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;
	t_pnp	*tmp1;

	tmp = *begin_list;
	tmp1 = NULL;
	while (f(tmp) != DLL_SUCCESS)
	{
		tmp1 = tmp;
		tmp = tmp->next;
	}
	if (tmp1)
		ft_add_node_nextto_np(tmp1, new);
	else
		ft_add_node_start_np(begin_list, new);
}
