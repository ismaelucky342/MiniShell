/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_node_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:50:18 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 15:50:19 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_ast_node_delete(void *node, t_node_type type)
{
	if (!node)
		return ;
	if (type == CMD)
		cmd_free((t_cmd *)node);
	else if (type == REDIR)
	{
		cmd_free(((t_redir *)node)->redir);
		ft_ast_node_delete(((t_redir *)node)->next, ((t_redir *)node)->type);
		free(node);
	}
	else if (type == PIPE || type == AND || type == OR)
	{
		ft_ast_node_delete(((t_node *)node)->left, ((t_node *)node)->type_left);
		ft_ast_node_delete(((t_node *)node)->right,
			((t_node *)node)->type_right);
		free(node);
	}
}
