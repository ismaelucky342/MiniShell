/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:15:01 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/18 12:43:24 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

/**
 * Iterates over the provided string starting at the position pointed to by `i`.
 * As `i` is an int pointer, after calling this function,
	the provided int position
 * will be after the brackets.
 *
 * @param str The string to iterate over.
 * @param i Pointer to the starting position in the string.
 */
void	ft_brackets(char *str, int *i)
{
	int	ctr;

	ctr = 1;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			state_quote_delimiter(str, i, '\'');
		else if (str[*i] == '(')
			++ctr;
		else if (str[*i] == ')')
			--ctr;
		if (ctr == 0)
			break ;
	}
}

/**
 * Waits for all child processes to finish and returns the
		exit code of the last process.
 *
 * @param last_pid The process ID of the last process.
 * @param last Pointer to the last tree node.
 * @return The exit code of the last process.
 */
static int	ft_wait_all(int last_pid, t_tree_node *last)
{
	int	status;
	int	last_exited;
	int	exit_code;

	last_exited = 0;
	exit_code = INT_MIN;
	status = 0;
	while (last_exited != -1)
	{
		last_exited = waitpid(-1, &status, 0);
		if (last_exited == last_pid && last_pid != 0)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = WTERMSIG(status) + 128;
		}
	}
	if (exit_code == INT_MIN)
		return (last->exit_code);
	return (exit_code);
}

static void	ft_superman(t_mini *boogeyman)
{
	char	*aux_pwd;
	char	*cwd;
	DIR		*dir;

	cwd = getcwd(NULL, 0);
	aux_pwd = boogeyman->aux_pwd;
	if (!cwd)
	{
		dir = opendir(aux_pwd);
		while (!dir && aux_pwd[0])
		{
			*(ft_strrchr(aux_pwd, '/')) = '\0';
			dir = opendir(aux_pwd);
		}
		if (dir)
		{
			closedir(dir);
			chdir(aux_pwd);
			update_prompt(boogeyman);
		}
	}
	free(cwd);
}

/**
 * Executes the commands in the abstract syntax tree
		and waits for them to finish.
 *
 * @param tree_node Pointer to the root of the abstract syntax tree.
 * @param boogeyman Pointer to the minishell structure.
 * @return The exit code of the last executed command.
 */
int	ft_exec_and_wait(t_ast_tree *tree_node, t_mini *boogeyman)
{
	int			std_backup[2];
	int			last_pid;
	int			tmp;
	t_tree_node	*last;

	ft_set_signal_print(1);
	std_backup[0] = dup(STDIN_FILENO);
	std_backup[1] = dup(STDOUT_FILENO);
	g_is_exec = 1;
	last_pid = -1;
	last = ft_pipes_interpreter(tree_node, boogeyman, &last_pid);
	tmp = ft_wait_all(last_pid, last);
	ft_dup2(std_backup[0], STDIN_FILENO);
	ft_dup2(std_backup[1], STDOUT_FILENO);
	ft_close(std_backup[0]);
	ft_close(std_backup[1]);
	ft_superman(boogeyman);
	if (g_is_exec == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_is_exec = 0;
	ft_set_signal_print(0);
	ft_putstr_fd("\x1b[0m", STDOUT_FILENO);
	if (tree_node->cmd_list->is_builtin == 1 && !tree_node->cmd_list->next)
		return (tree_node->cmd_list->exit_code);
	return (tmp);
}
