/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:07:14 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 22:30:49 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Frees the memory allocated for a redirection token.
 *
 * @param t A pointer to the redirection token to be freed.
 */
static void	free_redirections(void *t)
{
	t_rtoken	*tok;

	tok = t;
	freedom((void **)&tok->file_name);
	freedom((void **)&tok);
}

/**
 * Frees the memory allocated for a list of command nodes.
 *
 * @param cmd_list A pointer to the head of the command node list to be freed.
 */
static void	ft_free_node_list(t_tree_node *cmd_list)
{
	t_tree_node	*next;

	while (cmd_list)
	{
		next = cmd_list->next;
		ft_lstclear(&cmd_list->redirs_lst, &free_redirections);
		ft_free_array(cmd_list->args);
		freedom((void **)&cmd_list);
		cmd_list = next;
	}
}

/**
 * Frees the memory allocated for an AST tree.
 *
 * @param tree A pointer to the AST tree to be freed.
 * @return Always returns NULL.
 */
void	*ft_free_cmdtree(t_ast_tree *tree)
{
	if (tree->left)
		ft_free_cmdtree(tree->left);
	if (tree->right)
		ft_free_cmdtree(tree->right);
	ft_free_node_list(tree->cmd_list);
	if (tree->cmd_str)
		freedom((void **)&tree->cmd_str);
	if (tree->expanded_str)
		freedom((void **)&tree->expanded_str);
	if (tree->cmd_tokens)
		ft_lstclear(&tree->cmd_tokens, free_cmd_tok);
	freedom((void **)&tree);
	return (NULL);
}
