/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 11:08:49 by ismherna         ###   ########.fr       */
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

void print_prompt(t_global_state *state)
{
    char prompt[LINE_MAX];
    int i;
    int last;

    (!state->exit_status && state->exit_status) ? state->exit_status = state->exit_status : 0;
    if (!getcwd(prompt, LINE_MAX))
    {
        ft_printf_fd(2, "%s➜  %sminishell > %s", !state->exit_status ? COLOR_BOLD_GREEN_TEXT : COLOR_BOLD_RED_TEXT,
            COLOR_BOLD_CYAN_TEXT, COLOR_RESET);
        return;
    }
    i = -1;
    while (prompt[++i])
        if (prompt[i] == '/')
            last = i + 1;
    ft_printf_fd(2, "%s➜  %s%s > %s", !state->exit_status ? COLOR_BOLD_GREEN_TEXT : COLOR_BOLD_RED_TEXT, COLOR_BOLD_CYAN_TEXT,
        &prompt[last], COLOR_RESET);
}

void sig_handler(int signo)
{
    extern t_global_state g_state; // Usa una variable global externa para el estado compartido

    if (signo == SIGINT && ft_printf_fd(STDOUT_FILENO, "\n"))
    {
        g_state.reset = 1;
        g_state.exit_status = 130;
        print_prompt(&g_state);
    }
    else if (signo == SIGQUIT)
        ft_printf_fd(2, "\b\b  \b\b");
}

int main(int ac, char **av, char **env)
{
    int sloc;
    t_ast_node *ast;
    t_hashtable *env_hashtable;
    t_global_state g_state; // Define una variable de estado global
    t_token_data token_data; // Define y usa token_data

    (void)ac;
    (void)av;

    // Inicializa el estado global
    g_state.reset = 0;
    g_state.exit_status = 0;

    // Inicializa el entorno usando la tabla hash
    env_hashtable = ft_create_envhash(env);
    if (!env_hashtable)
    {
        perror("Failed to create environment hash");
        return (1);
    }

    sloc = 0;

    while (1)
    {
        signal(SIGINT, (void (*)(int))sig_handler);
        signal(SIGQUIT, (void (*)(int))sig_handler);

        if ((ast = ast_builder(sloc, &token_data))) // Asegúrate de pasar token_data
        {
#if DEBUG == 1
            ft_print_env(env_hashtable, 0);
            //tree_draw(ast); // Opcional: Dibuja el árbol si DEBUG está habilitado
#endif
            //sloc = ast_interpreter(ast);
            g_state.exit_status = sloc;
            ft_node_delete(&ast, CLEAN_NODE_AND_CHILDS);
        }
        else
            g_state.exit_status = 2; // Error en la construcción del AST

        print_prompt(&g_state);
    }

    free_all_malloc();
    ft_free_hashtable(env_hashtable);

    return (0);
}
