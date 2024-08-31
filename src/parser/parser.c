/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:38:41 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 18:38:42 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_user_prompt(t_exec *exec)
{
    char *prompt;
    char *prompt_tmp;

    prompt = get_env(*(exec->env), "USER");
    if (exec->exit_status)
        prompt_tmp = ft_strjoin(RED_INCIDATOR, prompt);
    else
        prompt_tmp = ft_strjoin(MAGENTA_INCIDATOR, prompt);
    free(prompt);
    
    return (prompt_tmp);
}

static char	*create_prompt_with_folder(char *folder, char *user_prompt)
{
    char *prompt_tmp;
    char *prompt;
    
    prompt = ft_strjoin(user_prompt, "@minishell:");
    free(user_prompt);

    prompt_tmp = color_string(folder, CYAN);
    prompt = ft_strjoin(prompt, prompt_tmp);
    free(prompt_tmp);
    
    prompt_tmp = ft_strjoin(prompt, "$ ");
    free(prompt);
    
    return (prompt_tmp);
}

char	*create_the_prompt(t_exec *exec)
{
    char *cwd;
    char *folder;
    char *user_prompt;
    char *prompt;

    cwd = getcwd(NULL, 0);
    folder = ft_strdup(ft_strrchr(cwd, '/') + 1);
    if (!folder)
        folder = ft_strdup(cwd);
    free(cwd);

    user_prompt = get_user_prompt(exec);
    prompt = create_prompt_with_folder(folder, user_prompt);
    free(folder);
    
    return (prompt);
}


t_node_type	parser(void **ast_root, t_exec *exec)
{
    char *command;
    t_token *tokens;
    t_node_type type_first;

    signal(SIGINT, parser_handler);
    signal(SIGQUIT, parser_handler);
    command = NULL;
    
    while (!command || !*command || *command == '\n')
    {
        free(command);
        command = create_the_prompt(exec);
        if (!command)
            exit_shell(exec, NULL, exec->exit_status);
    }
    command = check_unclosed(command, exec);
    
    if (!command)
        return (ERROR);
    tokens = get_next_token(command, NULL);
    free(command);
    type_first = split_by_operator(tokens, ast_root);
    
    if (type_first == ERROR && tokens)
    {
        exec->exit_status = 2;
    }
    else
    {
        process_ast(*ast_root);
    }
    return (type_first);
}
