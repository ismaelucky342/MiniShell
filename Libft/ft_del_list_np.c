/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_list_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:13 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 12:30:06 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_del_list_np(t_pnp **lst)
{
    t_pnp *tmp;
    t_pnp *tmp2;

    tmp = *lst;
    while (tmp)
    {
        tmp2 = tmp->next;
        free(tmp);  // Libera la memoria para el nodo actual
        tmp = tmp2;
    }
    *lst = NULL;
}

