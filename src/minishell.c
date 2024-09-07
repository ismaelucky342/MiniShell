/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 14:37:32 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_mem_context(t_mem_context *ctx)
{
	if (ctx)
	{
		ctx->allocated_list = NULL;
	}
}

static int	process_ast(int sloc, t_mem_context *ctx,
		t_hashtable *env_hashtable)
{
	t_ast_node	*ast;

	ast = ast_builder(sloc, ctx, env_hashtable);
	if (ast)
	{
		g_signals.exit_status = sloc;
		ft_node_delete(&ast, CLEAN_NODE_AND_CHILDS, ctx);
		return (0);
	}
	else
	{
		g_signals.exit_status = 2;
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
	t_mem_context	ctx;

	sloc = 0;
	(void)ac;
	(void)av;
	init_mem_context(&ctx);
	init_signal_context(&g_signals);
	g_signals.env_hashtable = ft_create_envhash(env);
	if (!g_signals.env_hashtable)
	{
		perror("Failed to create environment hash");
		return (1);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		if (process_ast(sloc, &ctx, g_signals.env_hashtable))
			break ;
	}
	cleanup(g_signals.env_hashtable, &ctx);
	return (g_signals.exit_status);
}
