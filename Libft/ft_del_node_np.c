/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:01:57 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:15:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_node_np(t_pnp **lst, t_pnp *del, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	if (*lst == del)
	{
		*lst = (*lst)->next;
		if (*lst)
			(*lst)->prev = NULL;
	}
	else
	{
		tmp = *lst;
		while (tmp && tmp->next != del)
			tmp = tmp->next;
		if (tmp == NULL)
			return ;
		tmp->next = del->next;
		if (del->next)
			del->next->prev = tmp;
	}
	if (f)
		f(del);
	free(del);
}
