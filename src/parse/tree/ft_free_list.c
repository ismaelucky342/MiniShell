/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:42:24 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:05:52 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_free_list(t_tree_node *cmd_list)
{
	t_tree_node	*next;

	while (cmd_list)
	{
		next = cmd_list->next;
		ft_lstclear(&cmd_list->redir_list, &ft_free_redirections);
		ft_array_free(cmd_list->args);
		free(cmd_list);
		cmd_list = next;
	}
}
