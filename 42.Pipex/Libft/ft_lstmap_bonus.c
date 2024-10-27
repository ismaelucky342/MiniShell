/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:18:02 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/24 13:18:03 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstcpy;
	t_list	*tmplst;
	t_list	*item;

	if (!lst || !f || !del)
		return (0);
	lstcpy = lst;
	tmplst = 0;
	while (lstcpy)
	{
		item = malloc(sizeof(t_list));
		if (item == NULL)
		{
			if (tmplst != NULL)
				ft_lstclear(&tmplst, del);
			else
				ft_lstclear(&item, del);
			return (NULL);
		}
		item->next = NULL;
		item->content = f(lstcpy->content);
		ft_lstadd_back(&tmplst, item);
		lstcpy = lstcpy->next;
	}
	return (tmplst);
}
