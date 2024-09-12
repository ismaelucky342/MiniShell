/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:45:12 by tharchen          #+#    #+#             */
/*   Updated: 2024/09/06 17:07:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
int	pid_save(int process_id, int opt)
{
	static t_pid_node	*list;
	t_pid_node			*new;
	int					sloc;

	list = NULL;
	sloc = 0;
	if (opt & BIN_OPT_ADD)
	{
		new = malloc(sizeof(t_pid_node));
		new->process_id = process_id;
		ft_add_node_end_np((t_pnp **)&list, (t_pnp *)new);
	}
	else if (opt & BIN_OPT_WAIT)
	{
		new = list;
		while (new)
		{
			waitpid(new->process_id, &sloc, 0);
			new = new->next;
		}
		return (sloc);
	}
	else if (opt & BIN_OPT_FREE)
		ft_del_list_np((t_pnp **)&list);
	return (0);
}
*/

/*
THIS FUNCTION OPEN A NEW PIPE AND ASSIGN THE WRITE SIDE TO THE LEFT CHILD
AND THE READ SIDE TO THE RIGHT ONE.

IT CLOSE THE STDOUT FD OF THE LEFT CHILD IF DIFFERENT STDOUT (1)
IT CLOSE THE STDIN FD OF THE RIGHT CHILD IF DIFFERENT STDIN (0)

RUN THE LEFT CHILD THEN CLOSE THE WRITE SIDE OF THE PIPE CAUSE THE LEFT CHILD
HAS FINISHED TO USE IT

RUN THE RIGHT CHILD THEN CLOSE THE READ SIDE OF THE PIPE CAUSE THE RIGHT
CHILD HAS FINISHED TO USE IT
*/

#include "../../../includes/minishell.h"

int	ast_cmdpipefirst_controller(t_ast_node *cmd)
{
	if (cmd->stdin != STDIN_FILENO)
		close(cmd->stdin);
	if (cmd->stdout != STDOUT_FILENO)
		close(cmd->stdout);
	if (pipe(cmd->pipe_ltor) == -1)
		return (asti_error(NULL, AST_INTERPRETER_ERROR_PIPE));
	cmd->stdout = cmd->pipe_ltor[PIPE_WRITE_END];
	if (redir_handle(cmd) == ERROR)
		return (-1);
	g_signals.exit_status = execute_fork(cmd, cmd->pipe_ltor[PIPE_READ_END]);
	close(cmd->pipe_ltor[PIPE_WRITE_END]);
	return (cmd->pipe_ltor[PIPE_READ_END]);
}

int	ast_cmdpipe_controller(t_ast_node *cmd, int fdread)
{
	if (cmd->stdin != STDIN_FILENO)
		close(cmd->stdin);
	if (cmd->stdout != STDOUT_FILENO)
		close(cmd->stdout);
	if (ast_parent_ispipe(cmd->parent))
	{
		if (pipe(cmd->pipe_ltor) == -1)
			return (asti_error(NULL, AST_INTERPRETER_ERROR_PIPE));
		cmd->stdout = cmd->pipe_ltor[PIPE_WRITE_END];
	}
	cmd->stdin = fdread;
	if (redir_handle(cmd) == ERROR)
		return (-1);
	if (ast_parent_ispipe(cmd->parent))
		g_signals.exit_status = execute_fork(cmd,
				cmd->pipe_ltor[PIPE_READ_END]);
	else
		g_signals.exit_status = execute_fork(cmd, 0);
	close(fdread);
	if (ast_parent_ispipe(cmd->parent))
	{
		close(cmd->pipe_ltor[PIPE_WRITE_END]);
		return (cmd->pipe_ltor[PIPE_READ_END]);
	}
	return (STDOUT_FILENO);
}

int	ast_subpipe_handle(t_ast_node *pipeline)
{
	int	fdread;

	if (pipeline->left->type == CMD)
	{
		fdread = ast_cmdpipefirst_controller(pipeline->left);
		if (fdread == -1)
			return (-1);
	}
	else
	{
		fdread = ast_subpipe_handle(pipeline->left);
		if (fdread == -1)
			return (-1);
	}
	fdread = ast_cmdpipe_controller(pipeline->right, fdread);
	if (fdread == -1)
		return (-1);
	return (fdread);
}

int	ast_pipe_handle(t_ast_node *pipeline)
{
	int	sig;

	if ((ast_subpipe_handle(pipeline)) == -1)
		return (1);
	sig = pid_save(0, BIN_OPT_WAIT | BIN_OPT_FREE);
	g_signals.exit_status = WEXITSTATUS(sig);
	return (WEXITSTATUS(sig));
}
