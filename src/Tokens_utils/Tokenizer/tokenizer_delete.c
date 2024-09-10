/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:40:47 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 16:33:28 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_tokenizer_delete(t_tokenizer **tz)
{
    if (*tz)
    {
        free((*tz)->current_line);
        free(*tz);
        *tz = NULL;
    }
}

