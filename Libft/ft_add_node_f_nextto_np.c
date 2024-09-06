/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_f_nextto_np.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:05:51 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:05:53 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_node_f_nextto_np(t_pnp **lst, t_pnp *new, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *lst;
	while (f(tmp) != DLL_SUCCESS)
		tmp = tmp->next;
	ft_add_node_nextto_np(tmp, new);
}
