/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_nextto_np.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:06:03 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:06:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_node_nextto_np(t_pnp *prev, t_pnp *new)
{
	new->next = prev->next;
	new->prev = prev;
	prev->next->prev = new;
	prev->next = new;
}
