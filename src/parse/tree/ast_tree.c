/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:50:53 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:07:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	assign_redirection_type(t_list *token_list, t_list **tmp)
{
	if (ft_strncmp("<", ((t_token *)token_list->data)->str, 2) == 0)
		((t_redirection_token *)(*tmp)->data)->type = INFILE_MASK;
	else if (ft_strncmp(">", ((t_token *)token_list->data)->str, 2) == 0)
		((t_redirection_token *)(*tmp)->data)->type = OUTFILE_MASK;
	else if (ft_strncmp("<<", ((t_token *)token_list->data)->str, 3) == 0)
		((t_redirection_token *)(*tmp)->data)->type = HEREDOC_MASK;
	else if (ft_strncmp(">>", ((t_token *)token_list->data)->str, 3) == 0)
		((t_redirection_token *)(*tmp)->data)->type = CONCATOUT_MASK;
}

static int	add_file_info(t_list *token_list, t_tree_node *current)
{
	t_list	*tmp;

	if (!token_list->next)
		return (KO);
	tmp = current->redir_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = ft_calloc(1, sizeof(t_list));
		tmp = tmp->next;
	}
	else
	{
		current->redir_list = ft_calloc(1, sizeof(t_list));
		tmp = current->redir_list;
	}
	tmp->data = ft_calloc(1, sizeof(t_redirection_token));
	((t_redirection_token *)tmp->data)->name
		= ft_strdup(((t_token *)token_list->next->data)->str);
	assign_redirection_type(token_list, &tmp);
	return (OK);
}

static int	ft_count_args(t_list *begin)
{
	t_token	*tkn;
	int		res;

	res = 0;
	if (begin)
		tkn = begin->data;
	while (begin && tkn->type != PIPE)
	{
		if (tkn->type >= ARG)
			++res;
		begin = begin->next;
		if (begin)
			tkn = begin->data;
	}
	return (res);
}

static int	fill_management(t_list **bgn, t_tree_node **current,
		t_tree_node **p_curr, int *i)
{
	if (((t_token *)(*bgn)->data)->type >= ARG)
		(*current)->args[(*i)++] = ft_strdup(((t_token *)(*bgn)->data)->str);
	else if (((t_token *)(*bgn)->data)->type == FILE_REDIR)
	{
		if (add_file_info((*bgn), (*current)))
			return (KO);
		(*bgn) = (*bgn)->next;
	}
	else if (((t_token *)(*bgn)->data)->type == PIPE)
	{
		if (!(*bgn)->next || ((t_token *)(*bgn)->next->data)->type == PIPE)
			return (KO);
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
	return (OK);
}

int	ft_fill_list(t_list *begin, t_ast_tree *tree_node)
{
	t_token		*tkn;
	t_tree_node	*current;
	t_tree_node	*p_curr;
	int			ctr[2];

	current = ft_calloc(1, sizeof(t_tree_node));
	if (!current)
		return (2);
	p_curr = current;
	tkn = begin->data;
	tree_node->cmd_list = current;
	current->args = ft_calloc(ft_count_args(begin) + 1, sizeof(char *));
	if (!current->args)
		return (2);
	if (tkn->type == PIPE)
		return (KO);
	ctr[0] = 0;
	while (begin)
	{
		ctr[1] = fill_management(&begin, &current, &p_curr, &ctr[0]);
		if (ctr[1])
			return (ctr[1]);
		begin = begin->next;
	}
	return (OK);
}
