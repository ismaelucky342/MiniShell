/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:55:50 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:55:51 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char *get_user_prompt(t_exec *exec)
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

static char *create_prompt_with_folder(char *folder, char *user_prompt)
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

char *create_the_prompt(t_exec *exec)
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
