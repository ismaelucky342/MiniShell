/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:53:04 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:53:05 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_words(t_ast_node *node)
{
	int		word_count = 0;
	int		i;
	t_cmd	*cmd;

	if (node->type == CMD)
	{
		cmd = (t_cmd *)node->value;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				word_count++;
				i++;
			}
		}
	}

	// Procesa los hijos del nodo si hay
	i = 0;
	while (i < node->children_count)
	{
		word_count += count_words(node->children[i]);
		i++;
	}

	return (word_count);
}

t_ast_node	*get_pipe(t_ast_node *node)
{
	t_ast_node	*result;

	if (node->type == PIPE)
		return (node);

	// Busca en los hijos
	int	i = 0;
	while (i < node->children_count)
	{
		result = get_pipe(node->children[i]);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}

t_ast_node	*get_operator(t_ast_node *node)
{
	t_ast_node	*result;

	if (node->type == AND || node->type == OR)
		return (node);

	// Busca en los hijos
	int	i = 0;
	while (i < node->children_count)
	{
		result = get_operator(node->children[i]);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}
