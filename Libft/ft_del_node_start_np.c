/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_start_np.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:01:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:16:00 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_node_start_np(t_pnp **lst, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	if (*lst == NULL)
		return ;
	tmp = *lst;
	*lst = (*lst)->next;
	if (*lst)
		(*lst)->prev = NULL;
	if (f)
		f(tmp);
	free(tmp);
}
