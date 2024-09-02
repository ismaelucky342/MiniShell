#include "libft.h"

void		ft_del_list_np(t_pnp **begin_list)
{
	t_pnp	*tmp;
	t_pnp	*tmp2;

	tmp = *begin_list;
	while (tmp)
	{
		tmp2 = tmp->next;
		mfree((void **)&tmp);
		tmp = tmp2;
	}
	*begin_list = NULL;
}
