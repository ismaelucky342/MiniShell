/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:00:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 11:56:42 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



t_ast_node *ast_builder(t_global_state *state, int sloc)
{
    t_astb tool;
    int ret;

    ret = init_tool(&tool, sloc, state); // Pasar el estado global aquí
    if (ret == EMPTY)
        return (ast_builder(state, sloc)); // Llamada recursiva con el estado global
    if (ret != ERROR && process(&tool) != ERROR)
    {
        ft_tokenizer_delete(&tool.ast_tokenizer);
        return (tool.ast_tree);
    }
    ft_tokenizer_delete(&tool.ast_tokenizer);
    return (NULL);
}


