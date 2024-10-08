/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_node_np.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:25:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/03/12 11:53:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	swap_ptr(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static inline void	swap_near(t_pnp *node_a, t_pnp *node_b)
{
	t_pnp	*tmp;

	if (node_a->prev == node_b && node_b->next == node_a)
	{
		tmp = node_a;
		node_a = node_b;
		node_b = tmp;
	}
	if (node_a->prev)
		node_a->prev->next = node_b;
	if (node_b->next)
		node_b->next->prev = node_a;
	node_b->prev = node_a->prev;
	node_a->next = node_b->next;
	node_b->next = node_a;
	node_a->prev = node_b;
}

static inline void	swap_all(t_pnp *node_a, t_pnp *node_b)
{
	t_pnp	*prev_a;
	t_pnp	*prev_b;
	t_pnp	*next_a;
	t_pnp	*next_b;

	prev_a = node_a->prev;
	prev_b = node_b->prev;
	next_a = node_a->next;
	next_b = node_b->next;
	swap_ptr((void **)&node_a->prev, (void **)&node_b->prev);
	swap_ptr((void **)&node_a->next, (void **)&node_b->next);
	if (prev_a)
		prev_a->next = node_b;
	if (prev_b)
		prev_b->next = node_a;
	if (next_a)
		next_a->prev = node_b;
	if (next_b)
		next_b->prev = node_a;
}

void	ft_swap_node_np(t_pnp **lst, t_pnp *node_a,
	t_pnp *node_b)
{
	if (!(lst) || !(*lst) || !node_a || !node_b)
		return ;
	if (*lst == node_a)
		*lst = node_b;
	else if (*lst == node_b)
		*lst = node_a;
	if (node_a->prev == node_b || node_b->prev == node_a
		|| node_a->prev == node_b || node_b->prev == node_a)
		swap_near(node_a, node_b);
	else
		swap_all(node_a, node_b);
}
