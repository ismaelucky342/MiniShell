/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach_node_f_np.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:01:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:01:38 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_foreach_node_f_np(t_pnp **lst, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;
	t_pnp	*tmp2;

	tmp = *lst;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		f(tmp);
		tmp = tmp2;
	}
}
