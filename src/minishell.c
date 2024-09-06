/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:59:56 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				g_reset;
unsigned int	g_exit;

static void	init_mem_context(t_mem_context *ctx)
{
	if (ctx)
	{
		ctx->allocated_list = NULL;
	}
}

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

static int	process_ast(int sloc, t_mem_context *ctx)
{
	t_ast_node		*ast;

	ast = ast_builder(sloc, ctx);
	if (ast)
	{
		g_exit = sloc;
		ft_node_delete(&ast, CLEAN_NODE_AND_CHILDS, ctx);
		return (0);
	}
	else
	{
		g_exit = 2;
		return (1);
	}
}

static void	cleanup(t_hashtable *env_hashtable, t_mem_context *ctx)
{
	free_all_malloc(ctx);
	ft_free_hashtable(env_hashtable);
}

int	main(int ac, char **av, char **env)
{
	int				sloc;
	t_hashtable		*env_hashtable;
	t_mem_context	ctx;

	sloc = 0;
	(void)ac;
	(void)av;
	init_mem_context(&ctx);
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
		if (process_ast(sloc, &ctx))
			break ;
	}
	cleanup(env_hashtable, &ctx);
	return (0);
}
