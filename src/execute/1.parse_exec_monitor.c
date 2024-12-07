/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.parse_exec_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:05:07 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 15:23:08 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    1. Remove outer brackets from the command string if present.
    2. Trim whitespace characters from the command string.
    3. Tokenize the command string.
    4. Expand tokens (variables and wildcards if implemented).
    5. Check for memory allocation errors.
    6. Parse tokens into an abstract syntax tree (AST).
    7. Execute the command and wait for it to finish.
    8. Handle redirection errors.
*/
int	ft_parse_and_exec_monitor(t_ast_tree *tree_node, t_mini *boogeyman)
{
	int	status;

	while (ft_has_brackets(tree_node->cmd_str))
		ft_remove_outer_brackets(tree_node->cmd_str);
	tree_node->expanded_str = ft_strtrim(tree_node->cmd_str, " \t\n\r\v");
	tree_node->cmd_tokens = tokenizer(tree_node->expanded_str);
	ft_expand_str_list(tree_node->cmd_tokens, boogeyman);
	if (!tree_node->cmd_tokens)
		ft_memory_err_exit(boogeyman);
	status = ft_ast_tree(tree_node->cmd_tokens, tree_node);
	if (!status)
		return (ft_exec_and_wait(tree_node, boogeyman));
	if (status == 2)
		ft_memory_err_exit(boogeyman);
	ft_putendl_fd("MiniShell: redirection error", STDERR_FILENO);
	boogeyman->cont = 0;
	return (2);
}
