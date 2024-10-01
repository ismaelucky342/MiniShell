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
//#include<stdio.h>
t_list	*ft_lstnew(void *data)
{
	t_list	*ft_ast_new_node;

	ft_ast_new_node = (t_list *)malloc(sizeof(t_list));
	if (!ft_ast_new_node)
		return (NULL);
	ft_ast_new_node->data = data;
	ft_ast_new_node->next = (NULL);
	return (ft_ast_new_node);
}
/*int		main(){
	int data = 42;
	t_list *nodo = ft_lstnew(&data);

	printf("nuevo nodo %d\n", *((int *)nodo->data));
	free(nodo);
	return (OK);
}*/