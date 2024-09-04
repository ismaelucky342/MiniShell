/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_start_np.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:01:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:01:53 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_del_node_start_np(t_pnp **begin_list, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	*begin_list = (*begin_list)->next;
	(*begin_list)->next->prev = NULL;
	if (f)
		f(tmp);
	mfree((void **)&tmp);
}
