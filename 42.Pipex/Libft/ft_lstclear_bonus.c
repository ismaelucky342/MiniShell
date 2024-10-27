/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:17:46 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/24 13:17:52 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*item;
	t_list	*next_item;

	if (!lst || !del)
		return ;
	item = *lst;
	while (item != NULL)
	{
		next_item = item->next;
		del(item->content);
		free(item);
		item = next_item;
	}
	*lst = NULL;
}
