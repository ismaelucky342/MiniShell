/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:05:44 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:05:46 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_node_end_np(t_pnp **lst, t_pnp *new)
{
	t_pnp	*tmp;

	if (!(*lst))
	{
		*lst = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = *lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}
