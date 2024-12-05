/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/02/12 11:51:58 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ft_ast_new_node;

	ft_ast_new_node = (t_list *)malloc(sizeof(t_list));
	if (!ft_ast_new_node)
		return (NULL);
	ft_ast_new_node->content = content;
	ft_ast_new_node->next = (NULL);
	return (ft_ast_new_node);
}

/*//#include<stdio.h>
int		main(){
	int content = 42;
	t_list *nodo = ft_lstnew(&content);

	printf("nuevo nodo %d\n", *((int *)nodo->content));
	free(nodo);
	return (OK);
}*/
