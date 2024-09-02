#include "libft.h"


void		ft_add_node_f_nextto_np(
	t_pnp **begin_list, t_pnp *new, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	while (f(tmp) != DLL_SUCCESS)
		tmp = tmp->next;
	ft_add_node_nextto_np(tmp, new);
}
