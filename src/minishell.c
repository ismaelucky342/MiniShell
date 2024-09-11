/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/11 19:50:14 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int	process_ast(int sloc,t_hashtable *env_hashtable)
{
	t_ast_node	*ast;

	ast = ast_builder(sloc, env_hashtable);
	if (ast)
	{
		g_signals.exit_status = sloc;
		ft_node_delete(&ast, CLEAN_NODE_AND_CHILDS);
		return (0);
	}
	else
	{
		g_signals.exit_status = 2;
		return (1);
	}
}

static void	cleanup(t_hashtable *env_hashtable)
{
	if (env_hashtable)
		free_env_hashtable(env_hashtable);
}

int main(int ac, char **av, char **env)
{
    int sloc;

    sloc = 0;
    (void)ac;
    (void)av;
    init_signal_context(&g_signals);
    g_signals.env_hashtable = ft_create_envhash(env);
	ft_print_env(g_signals.env_hashtable, 0); 
    if (!g_signals.env_hashtable)
    {
        perror("Failed to create environment hash");
        cleanup(g_signals.env_hashtable);
        return (1);
    }
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    while (1)
    {
        if (process_ast(sloc, g_signals.env_hashtable))
            break;
    }
    cleanup(g_signals.env_hashtable);
    return (g_signals.exit_status);
}
