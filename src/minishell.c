/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 14:06:12 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				g_reset;

unsigned int	g_exit;

void	sig_handler(int signo)
{
	if (signo == SIGINT && ft_printf_fd(STDOUT_FILENO, "\n"))
	{
		g_reset = 1;
		g_exit = 130;
		print_prompt(0);
	}
	else if (signo == SIGQUIT)
		ft_printf_fd(2, "\b\b  \b\b");
}

static int	process_ast(int sloc)
{
	t_ast_node	*ast;

	ast = ast_builder(sloc);
	if (ast)
	{
		g_exit = sloc;
		ft_node_delete(&ast, CLEAN_NODE_AND_CHILDS);
		return (0);
	}
	else
	{
		g_exit = 2;
		return (1);
	}
}

static void	cleanup(t_hashtable *env_hashtable)
{
	free_all_malloc();
	ft_free_hashtable(env_hashtable);
}

int	main(int ac, char **av, char **env)
{
	int			sloc;
	t_hashtable	*env_hashtable;

	sloc = 0;
	(void)ac;
	(void)av;
	env_hashtable = ft_create_envhash(env);
	if (!env_hashtable)
	{
		perror("Failed to create environment hash");
		return (1);
	}
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if (process_ast(sloc))
			break ;
	}
	cleanup(env_hashtable);
	return (0);
}
