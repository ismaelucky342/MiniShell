/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:52:23 by ismherna          #+#    #+#             */
/*   Updated: 2024/07/21 13:53:11 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*ft_add_redir_node(t_redir *redir_list, t_token *token_list)
{
	t_redir	*redir_node;
	t_redir	*redir_list_holder;

	token_list = token_list->next;
	if (!token_list)
		return (NULL);
	redir_node = ft_init_redir_node(token_list->token_type);
	redir_node->value = ft_strdup(token_list->value);
	if (!redir_list)
		return (redir_node);
	redir_list_holder = redir_list;
	while (redir_list->next)
		redir_list = redir_list->next;
	redir_list->next = redir_node;
	redir_list = redir_list_holder;
	return (redir_list);
}