/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 22:32:02 by tharchen          #+#    #+#             */
/*   Updated: 2024/09/06 17:30:40 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

int	ast_parent_ispipe(t_ast_node *node)
{
	return (node && node->parent && node->parent->type == SEPARATOR
		&& node->parent->separators->type == TOKEN_PIPE);
}

int	asti_error(char *name, int opt)
{
	if (opt == AST_INTERPRETER_ERROR_OPEN)
		ft_dprintf(2, "minishell: %s: %s\n", name, strerror(errno));
	else if (opt == AST_INTERPRETER_ERROR_PIPE)
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
	return (ERROR);
}

int	ast_cmd_controller(t_ast_node *cmd)
{
	if (redir_handle(cmd) == ERROR)
		return (ERROR);
	g_exit = execute_simple(cmd);
	if (cmd->stdout != STDOUT_FILENO)
		close(cmd->stdout);
	if (cmd->stdin != STDIN_FILENO)
		close(cmd->stdin);
	return (g_exit);
}

int	ast_controller(t_ast_node *node)
{
	if (node->type == SEPARATOR)
		return (ast_sep_controller(node));
	else if (node->type == CMD)
		return (ast_cmd_controller(node));
	else
		return (SUCCESS);
}

int	ast_interpreter(t_ast_node *ast)
{
	return (ast_controller(ast));
}