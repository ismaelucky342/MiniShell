/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:01:57 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 15:40:42 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_node_np(t_pnp **lst, t_pnp *del, void (*f)(t_pnp *curr),
		t_mem_context *ctx)
{
	t_pnp	*tmp;

	tmp = *lst;
	if (tmp == del)
	{
		*lst = (*lst)->next;
		if (*lst)
			(*lst)->prev = NULL;
	}
	else
	{
		while (tmp->next != del)
			tmp = tmp->next;
		if (tmp->next == NULL)
			return ;
		tmp->next = del->next;
		if (tmp->next)
			tmp->next->prev = tmp;
	}
	if (f)
		f(del);
	mfree(ctx, (void **)&del);
}
