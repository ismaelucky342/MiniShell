/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_list_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:13 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:02:15 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_list_np(t_pnp **lst)
{
	t_pnp	*tmp;
	t_pnp	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		mfree((void **)&tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}
