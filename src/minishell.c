/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 13:23:49 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
int				g_reset;

unsigned int	g_exit;
=======
void	print_prompt(int sloc)
{
	char	prompt[LINE_MAX];
	int		i;
	int		last;

	(!g_exit && sloc) ? g_exit = sloc : 0;
	if (!getcwd(prompt, LINE_MAX))
	{
		ft_printf_fd(2, "%s➜  %sminishell > %s", !g_exit ? COLOR_BOLD_GREEN_TEXT : COLOR_BOLD_RED_TEXT,
			COLOR_BOLD_CYAN_TEXT, COLOR_RESET);
		return ;
	}
	i = -1;

	while (prompt[++i])
		if (prompt[i] == '/')
			last = i + 1;
	ft_printf_fd(2, "%s➜  %s%s > %s", !g_exit ? COLOR_BOLD_GREEN_TEXT : COLOR_BOLD_RED_TEXT, COLOR_BOLD_CYAN_TEXT,
		&prompt[last], COLOR_RESET);
}
>>>>>>> 549d495cad994d844209ca1e6b3a26e09eda232a

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

<<<<<<< HEAD
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

=======
>>>>>>> 549d495cad994d844209ca1e6b3a26e09eda232a
int	main(int ac, char **av, char **env)
{
	int			sloc;
	int			ast;
	t_hashtable	*env_hashtable;

	sloc = 0;
	ast = 0;
	(void)ac;
	(void)av;
	env_hashtable = ft_create_envhash(env);
	if (!env_hashtable)
	{
		perror("Failed to create environment hash");
		return (1);
	}
<<<<<<< HEAD
=======

	//ft_print_env(env_hashtable, 0);
	sloc = 0;
	g_exit = 0;

>>>>>>> 549d495cad994d844209ca1e6b3a26e09eda232a
	while (1)
	{
		setup_signal_handlers();
		if (process_ast(sloc))
			break ;
		sloc = ast_interpreter(ast);
	}
	cleanup(env_hashtable);
	return (0);
}
