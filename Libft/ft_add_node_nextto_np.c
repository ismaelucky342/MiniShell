#include "libft.h"

void		ft_add_node_nextto_np(t_pnp *prev, t_pnp *new)
{
	new->next = prev->next;
	new->prev = prev;
	prev->next->prev = new;
	prev->next = new;
}
