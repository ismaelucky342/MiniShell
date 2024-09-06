/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_prevto_np.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:06:09 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:06:11 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_node_prevto_np(t_pnp **start, t_pnp *next, t_pnp *new)
{
	if (!new && !next && !(*start))
		return ;
	if (*start == next)
		ft_add_node_start_np(start, new);
	else
	{
		new->next = next;
		new->prev = next->prev;
		next->prev->next = new;
		next->prev = new;
	}
}
