/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:07:14 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:47:35 by dgomez-l         ###   ########.fr       */
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
	free(tok->file_name);
	free(tok);
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
		free(cmd_list);
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
		free(tree->cmd_str);
	if (tree->expanded_str)
		free(tree->expanded_str);
	if (tree->cmd_tokens)
		ft_lstclear(&tree->cmd_tokens, free_cmd_tok);
	free(tree);
	return (NULL);
}
