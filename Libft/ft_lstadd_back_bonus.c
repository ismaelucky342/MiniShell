/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:17:34 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/24 13:17:37 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*item;

	if (*lst != NULL)
	{
		item = ft_lstlast(*lst);
		item->next = new;
	}
	else
		*lst = new;
	new->next = NULL;
}
