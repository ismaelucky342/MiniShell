/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:02:10 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/04 15:45:02 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_filter(t_redir_token *token)
{
	if (token->type == INFILE_MASK)
		return (open(token->name, O_RDONLY));
	else if (token->type == OUTFILE_MASK)
		return ((token->name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (token->type == HEREDOC_MASK)
		return ((token->name, O_RDONLY));
	else if (token->type == CONCATOUT_MASK)
		return ((token->name, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else
		return (-1);
}

static t_bool	ft_exedirs(t_list *redirs, t_minishell *boogeyman)
{
	t_redir_token		*token;
	int						fd;

	fd = -1;
	while (redirs)
	{
		token = (t_redir_token *)redirs->data;
		fd = ft_filter(token);
		if (fd < 0)
			return (perror("Minishell"), ft_hitman(boogeyman), FALSE);
		redirs = redirs->next;
	}
	return(FALSE);
}

t_bool	ft_exec_ve(t_tree_node *node, t_minishell *boogeyman, t_bool single)
{
	char	*cmd_path;
	char	**env;
	char	**args;
	
	env = boogeyman->envp;
	boogeyman->envp = NULL;
	args = node->args;
	node->args = NULL;
	if (single == FALSE && node->redir_list)
		if (ft_exedirs(node->redir_list, boogeyman) == FALSE)
			exit(EXIT_FAILURE);
	cmd_path = ft_where_is_comm_b(args[0], env);
	ft_hitman(boogeyman);
	execve(cmd_path, args, env);
	perror(cmd_path);
	ft_array_free(env);
	ft_array_free(args);
	free(cmd_path);
	exit(EXIT_FAILURE);
}
