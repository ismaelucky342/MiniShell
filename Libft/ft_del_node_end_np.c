/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:05 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:15:50 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_node_end_np(t_pnp **lst, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;
	t_pnp	*prev;

	tmp = *lst;
	if (tmp == NULL)
		return ;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp != *lst)
	{
		prev = tmp->prev;
		if (prev)
			prev->next = NULL;
	}
	else
		*lst = NULL;
	if (f)
		f(tmp);
	free(tmp);
}
