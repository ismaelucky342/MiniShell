/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:59:26 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 16:28:52 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Compares the token string with redirection symbols and sets the
		redirection type in the redirection token.
 * 
 * @param tkn_lst The list of tokens.
 * @param tmp A pointer to the current redirection token list.
 */
static void	red_compare(t_list *tkn_lst, t_list **tmp)
{
	if (ft_strncmp("<", ((t_token *)tkn_lst->content)->str, 2) == 0)
		((t_rtoken *)(*tmp)->content)->redir_type = M_INFILE;
	else if (ft_strncmp(">", ((t_token *)tkn_lst->content)->str, 2) == 0)
		((t_rtoken *)(*tmp)->content)->redir_type = M_OUT;
	else if (ft_strncmp("<<", ((t_token *)tkn_lst->content)->str, 3) == 0)
		((t_rtoken *)(*tmp)->content)->redir_type = M_HEREDOC;
	else if (ft_strncmp(">>", ((t_token *)tkn_lst->content)->str, 3) == 0)
		((t_rtoken *)(*tmp)->content)->redir_type = M_CONCAT_OUT_ST;
}

/**
 * @brief
 * Sets the file information for the current tree node based on the token list.
 * 
 * @param tkn_lst The list of tokens.
 * @param current The current tree node.
 * @return 0 on success, 1 if there is no next token.
 * @warning MALLOC. Return for malloc failure = ?
 */
static int	set_file_info(t_list *tkn_lst, t_tree_node *current)
{
	t_list	*tmp;

	if (!tkn_lst->next)
		return (1);
	tmp = current->redirs_lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = ft_calloc(1, sizeof(t_list));
		tmp = tmp->next;
	}
	else
	{
		current->redirs_lst = ft_calloc(1, sizeof(t_list));
		tmp = current->redirs_lst;
	}
	tmp->content = ft_calloc(1, sizeof(t_rtoken));
	((t_rtoken *)tmp->content)->file_name = ft_strdup(((t_token *)
				tkn_lst->next->content)->str);
	red_compare(tkn_lst, &tmp);
	return (0);
}

/**
 * Counts the number of arguments in the token list until a PIPE token
		is encountered.
 * 
 * @param begin The beginning of the token list.
 * @return The number of arguments.
 */
static int	ft_count_args(t_list *begin)
{
	t_token	*tkn;
	int		res;

	res = 0;
	if (begin)
		tkn = begin->content;
	while (begin && tkn->type != PIPE)
	{
		if (tkn->type >= ARG)
			++res;
		begin = begin->next;
		if (begin)
			tkn = begin->content;
	}
	return (res);
}

/**
 * Manages the filling of the command list by processing tokens and setting up
 * the tree nodes accordingly.
 * 
 * @param bgn The beginning of the token list.
 * @param current The current tree node.
 * @param p_curr The previous current tree node.
 * @param i The index for arguments.
 * @return 0 on success, 1 on error, 2 on memory allocation failure.
 * @warning MALLOC. Return for malloc failure = 2
 */
static int	fill_management(t_list **bgn, t_tree_node **current,
		t_tree_node **p_curr, int *i)
{
	if (((t_token *)(*bgn)->content)->type >= ARG)
		(*current)->args[(*i)++] = ft_strdup(((t_token *)(*bgn)->content)->str);
	else if (((t_token *)(*bgn)->content)->type == FILE_REDIR)
	{
		if (set_file_info((*bgn), (*current)))
			return (1);
		(*bgn) = (*bgn)->next;
	}
	else if (((t_token *)(*bgn)->content)->type == PIPE)
	{
		if (!(*bgn)->next || ((t_token *)(*bgn)->next->content)->type == PIPE)
			return (1);
		(*current) = ft_calloc(1, sizeof(t_tree_node));
		if (!(*current))
			return (2);
		(*p_curr)->next = (*current);
		(*p_curr) = (*current);
		(*current)->args = ft_calloc(ft_count_args((*bgn)->next) + 1,
				sizeof(char *));
		(*i) = 0;
		if (!(*current)->args)
			return (2);
	}
	return (0);
}

/**
 * Fills the command list in the abstract syntax tree (AST) by processing
		the token list.
 * 
 * @param begin The beginning of the token list.
 * @param tree_node The AST tree node.
 * @return 0 on success, 1 on error, 2 on memory allocation failure.
 * @warning MALLOC. Return for malloc failure = 2.
 */
int	ft_ast_tree(t_list *begin, t_ast_tree *tree_node)
{
	t_token			*tkn;
	t_tree_node		*current;
	t_tree_node		*p_curr;
	int				ctr[2];

	current = ft_calloc(1, sizeof(t_tree_node));
	if (!current)
		return (2);
	p_curr = current;
	tkn = begin->content;
	tree_node->cmd_list = current;
	current->args = ft_calloc(ft_count_args(begin) + 1, sizeof(char *));
	if (!current->args)
		return (2);
	if (tkn->type == PIPE)
		return (1);
	ctr[0] = 0;
	while (begin)
	{
		ctr[1] = fill_management(&begin, &current, &p_curr, &ctr[0]);
		if (ctr[1])
			return (ctr[1]);
		begin = begin->next;
	}
	return (0);
}
