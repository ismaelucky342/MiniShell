/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:10:59 by ismherna          #+#    #+#             */
/*   Updated: 2024/07/21 14:11:00 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast	*ft_create_tree_node(t_token *token_list, int nb_element)
{
	t_ast	*node;
	int		index;

	index = 0;
	node = ft_malloc_node(nb_element);
	node->node_type = NODE_CMD;
	if (token_list->token_type == TOKEN_PIPE)
		node->node_type = NODE_PIPE;
	while (nb_element-- > 0)
	{
		if (ft_is_redir(token_list->token_type) == 1)
		{
			node->redir_list = ft_add_rnode(node->redir_list, token_list);
			if (token_list->next)
				token_list = token_list->next;
			nb_element--;
		}
		else
		{
			if (token_list->value)
				node->value[index] = ft_strdup(token_list->value);
			index++;
		}
		token_list = token_list->next;
	} return (node);
}