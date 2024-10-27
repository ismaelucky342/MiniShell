/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:40:36 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:31:55 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	*ft_free_ast_tree(t_ast_tree *tree)
{
	if (tree->left)
		ft_free_ast_tree(tree->left);
	if (tree->right)
		ft_free_ast_tree(tree->right);
	ft_free_list(tree->cmd_list);
	if (tree->cmd_str)
		free(tree->cmd_str);
	if (tree->expanded_str)
		free(tree->expanded_str);
	if (tree->cmd_tokens)
		ft_lstclear(&tree->cmd_tokens, free_cmd_token);
	free(tree);
	return (NULL);
}
