/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:05 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 15:43:48 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_node_end_np(t_pnp **lst, void (*f)(t_pnp *curr),
		t_mem_context *ctx)
{
	t_pnp	*tmp;

	tmp = *lst;
	if (tmp == NULL)
		return ;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp != *lst)
	{
		tmp->prev->next = NULL;
	}
	if (f)
		f(tmp);
	mfree(ctx, (void **)&tmp);
}
