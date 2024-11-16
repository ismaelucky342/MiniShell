/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hitman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:58:00 by apollo            #+#    #+#             */
/*   Updated: 2024/11/16 11:32:36 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Libera la memoria de la estructura t_minishell y cierra los file descriptors.
 *
 * @param boogeyman Puntero a la estructura t_minishell a liberar.
 */
void ft_hitman(t_minishell *boogeyman)
{
    if (!boogeyman)
        return ;
    if (boogeyman->history_fd >= 0)
        close(boogeyman->history_fd);
    if (boogeyman->cmd_tree)
    {
        ft_free_ast_tree(boogeyman->cmd_tree); 
        boogeyman->cmd_tree = NULL;
    }
    if (boogeyman->envp)
    {
        for (long i = 0; i < boogeyman->env_elems; i++)
        {
            free(boogeyman->envp[i]);
        }
        free(boogeyman->envp);
        boogeyman->envp = NULL;
    }
    if (boogeyman->ft_prompt)
    {
        free(boogeyman->ft_prompt);
        boogeyman->ft_prompt = NULL;
    }
    free(boogeyman);
}
