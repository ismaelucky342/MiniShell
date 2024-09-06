/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:58:54 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 16:01:02 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_node_delete(t_ast_node **node, int opt, t_mem_context *ctx)
{
	if (node == NULL || *node == NULL)
		return ;
	ft_token_list_del(&(*node)->av);
	ft_token_list_del(&(*node)->redirections);
	ft_token_list_del(&(*node)->separators);
	if (opt == CLEAN_NODE_AND_CHILDS)
	{
		if ((*node)->left != NULL)
			ft_node_delete(&(*node)->left, opt, ctx);
		if ((*node)->right != NULL)
			ft_node_delete(&(*node)->right, opt, ctx);
	}
	mfree(ctx, (void **)node);
}
