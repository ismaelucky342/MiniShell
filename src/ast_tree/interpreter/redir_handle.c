/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:44:24 by tharchen          #+#    #+#             */
/*   Updated: 2024/09/06 17:13:47 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_handle__each(t_ast_node *cmd, t_token *tmp_redir, t_token *tmp_file)
{
	if (tmp_redir->type == TOKEN_REDIR_INPUT)
	{
		if (cmd->stdin != STDIN_FILENO)
			close(cmd->stdin);
		cmd->stdin = open(tmp_file->value, O_RDWR, 0644);
		if (cmd->stdin == -1)
		{
			cmd->stdin = STDIN_FILENO;
			return (asti_error(tmp_file->value, AST_INTERPRETER_ERROR_OPEN));
		}
	}
	else if (tmp_redir->type == TOKEN_REDIR_OUTPUT)
	{
		if (cmd->stdout != STDOUT_FILENO)
			close(cmd->stdout);
		cmd->stdout = open(tmp_file->value, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (cmd->stdout == -1)
		{
			cmd->stdout = STDOUT_FILENO;
			return (asti_error(tmp_file->value, AST_INTERPRETER_ERROR_OPEN));
		}
	}
	else if (tmp_redir->type == TOKEN_DBL_REDIR_OUTPUT)
	{
		if (cmd->stdout != STDOUT_FILENO)
			close(cmd->stdout);
		cmd->stdout = open(tmp_file->value, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (cmd->stdout == -1)
		{
			cmd->stdout = STDOUT_FILENO;
			return (asti_error(tmp_file->value, AST_INTERPRETER_ERROR_OPEN));
		}
	}
	return (SUCCESS);
}

/*
** THIS FUNCTION WILL OPEN ALL REDIRECTION AND ASSIGN TO cmd->stdout OR
** cmd->stdin
** THE FD JUST OPENED. BEFORE THE ASSIGNMENT, IT CLOSE THE FD PRESENT IN
** cmd->stdout OR cmd->stdin IF THEY ARE DIFFERENT OF STDOUT OR STDIN
*/

int	redir_handle(t_ast_node *cmd)
{
	t_token	*tmp_redir;
	t_token	*tmp_file;
	int		ret;

	tmp_redir = cmd->redirections;
	tmp_file = cmd->files;
	while (tmp_redir && tmp_file)
	{
		if ((ret = redir_handle__each(cmd, tmp_redir, tmp_file)) != SUCCESS)
			return (ret);
		tmp_redir = tmp_redir->next;
		tmp_file = tmp_file->next;
	}
	return (SUCCESS);
}
