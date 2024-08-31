/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_new_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:49:52 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 15:49:53 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_ast_node	*ft_ast_new_node(void)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = ERROR;
	node->value = NULL;
	node->children = NULL;
	node->children_count = 0;
	return (node);
}
