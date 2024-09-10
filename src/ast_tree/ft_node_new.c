/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:59:06 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 12:14:13 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*ft_node_new(t_ast_node_type type)
{
	t_ast_node	*new;

	new = malloc(sizeof(t_ast_node));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->stdin = STDIN_FILENO;
	new->stdout = STDOUT_FILENO;
	return (new);
}
