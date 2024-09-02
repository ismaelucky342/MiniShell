/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/02 12:47:37 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
RESUMEN: 
1. Iniciar shell -> 2. Configurar terminal 
-> 3. Leer comando -> 4. Parsear comando (AST) 
-> 5. Ejecutar comando -> 6. Limpiar recursos 
-> 7. Reiniciar bucle

*/
#include "../includes/minishell.h"

void	print_prompt(int sloc)
{
	char	prompt[LINE_MAX];
	int		i;
	int		last;

	(!g_exit && sloc) ? g_exit = sloc : 0;
	if (!getcwd(prompt, LINE_MAX))
	{
		ft_dprintf(2, "%s➜  %sminishell > %s", !g_exit ? C_G_GREEN : C_G_RED,
			C_G_CYAN, C_RES);
		return ;
	}
	i = -1;
	while (prompt[++i])
		if (prompt[i] == '/')
			last = i + 1;
	ft_dprintf(2, "%s➜  %s%s > %s", !g_exit ? C_G_GREEN : C_G_RED, C_G_CYAN,
		&prompt[last], C_RES);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT && ft_dprintf(STDOUT, "\n"))
	{
		g_reset = 1;
		g_exit = 130;
		print_prompt(0);
	}
	else if (signo == SIGQUIT)
		ft_dprintf(2, "\b\b  \b\b");
}


int	main(int ac, char **av, char **env)
{
	int			sloc;
	t_ast_node		*ast;
	t_hashtable	*env_hashtable;

	// Inicializa el entorno usando la tabla hash
	env_hashtable = ft_create_envhash(env);
	if (!env_hashtable)
	{
		perror("Failed to create environment hash");
		return (1);
	}

	ft_print_env(env_hashtable, 0);

	sloc = 0;
	g_exit = 0;

	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);

		if ((ast = ast_builder(sloc)))
		{
#if DEBUG == 1
			tree_draw(ast); // Opcional: Dibuja el árbol si DEBUG está habilitado
#endif
			sloc = ast_interpreter(ast);
			g_exit = sloc;
			node__del(&ast, RECURCIVLY);
		}
		else
		{
			g_exit = 2; // Error en la construcción del AST
		}
	}

	// Libera todos los recursos y la memoria
	free_all_malloc();

	// Libera la tabla hash y sus elementos
	ft_free_hashtable(env_hashtable);

	return (0);
}

