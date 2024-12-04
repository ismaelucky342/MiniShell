/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:02:10 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/04 16:14:12 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief
 * Filters the open() flags depending on the redirection type.
 * @param token
 * Current redirection token.
 * @return
 * Returns the resulting fd of the open() function.
 */
static int	ft_filter(t_redir_token *token)
{
	if (token->type == INFILE_MASK)
		return (open(token->name, O_RDONLY));
	else if (token->type == OUTFILE_MASK)
		return (open(token->name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (token->type == HEREDOC_MASK)
		return (open(token->name, O_RDONLY));
	else if (token->type == CONCATOUT_MASK)
		return (open(token->name, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else
		return (-1);
}

static t_bool	ft_duper(t_redir_token *token, int fd)
{
	if (token->type == INFILE_MASK || token->type == HEREDOC_MASK)
	{
		if(dup2(fd, STDIN_FILENO) < 0)
			return (close(fd), FALSE);
	}
	else if (token->type == OUTFILE_MASK || token->type == HEREDOC_MASK)
	{
		if(dup2(fd, STDOUT_FILENO) < 0)
			return (close(fd), FALSE);
	}
	else
		return (close(fd), FALSE);
	return (close(fd), TRUE);
}

/**
 * @brief
 * Execution redirections handler.
 * @param redirs
 * List with the redirection tokens.
 * @param boogeyman
 * Pointer to the superstructure for env and memory purposes.
 * @return
 * Returns a boolean of whether or not the process should finish.
 */
static t_bool	ft_exredirs(t_list *redirs, t_minishell *boogeyman)
{
	t_redir_token		*token;
	int						fd;

	while (redirs)
	{
		token = (t_redir_token *)redirs->data;
		fd = ft_filter(token);
		if (fd < 0 || !ft_duper(token, fd))
			return (perror(token->name), ft_hitman(boogeyman), FALSE);
		redirs = redirs->next;
	}
	return (TRUE);
}

/**
 * @brief
 * Handles redirs and ENV search to send execve() the correct values.
 * @param node
 * Node of the executed command.
 * @param boogeyman
 * Pointer to the superstructure for env and memory purposes.
 */
void	ft_exec_ve(t_tree_node *node, t_minishell *boogeyman)
{
	char	*cmd_path;
	char	**env;
	char	**args;
	
	if (node->redir_list)
		if (ft_exredirs(node->redir_list, boogeyman) == FALSE)
			exit(EXIT_FAILURE);
	env = boogeyman->envp;
	boogeyman->envp = NULL;
	args = node->args;
	node->args = NULL;
	cmd_path = ft_where_is_comm_b(args[0], env);
	ft_hitman(boogeyman);
	execve(cmd_path, args, env);
	perror(cmd_path);
	ft_array_free(env);
	ft_array_free(args);
	free(cmd_path);
	exit(EXIT_FAILURE);
}
