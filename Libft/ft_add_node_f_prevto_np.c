/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_f_prevto_np.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:05:56 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:05:57 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_node_f_prevto_np(
	t_pnp **lst, t_pnp *new, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;
	t_pnp	*tmp1;

	tmp = *lst;
	tmp1 = NULL;
	while (f(tmp) != DLL_SUCCESS)
	{
		tmp1 = tmp;
		tmp = tmp->next;
	}
	if (tmp1)
		ft_add_node_nextto_np(tmp1, new);
	else
		ft_add_node_start_np(lst, new);
}
