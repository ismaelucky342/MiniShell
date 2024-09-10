/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:15:13 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 13:12:09 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_tokenizer *ft_tokenizer_new(int sloc, t_hashtable *env_hashtable)
{
    t_tokenizer *tz;

    tz = malloc(sizeof(t_tokenizer));
    if (tz == NULL)
        return (NULL);
    
    tz->current_line = NULL;
    tz->current_position = 0;
    tz->start_index = 0;
    tz->line_length = 0;
    tz->current_char = '\0';
    tz->line_start_char = '\0';

    if (ft_tokenizer_refill_line(tz, sloc, env_hashtable) == ERROR)
    {
        ft_tokenizer_delete(&tz);
        return (NULL);
    }
    return (tz);
}

