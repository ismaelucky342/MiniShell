/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:54:02 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 11:50:59 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// Cambia el tipo de la función quote_as_token para que reciba un t_character_type en lugar de un puntero a int
void quote_as_token(t_tokenizer *tz, t_character_type *search) // el contenido bajo "" como un token
{
    // Asigna el valor a search
    *search = ft_tokenizer_isquote(tz);

    // Llama a ft_tokenizer_pass_quotes con el valor correcto
    if (*search != CHAR_TYPE_NONE) // Asegúrate de que *search sea un tipo válido
        ft_tokenizer_pass_quotes(tz, *search);

    ft_tokenizer_advance(tz, 1);
}

t_token *ft_tokenizer_handle_defined_token(t_tokenizer *tz)
{
    int index;
    
    while (ft_tokenizer_istype(tz, CHAR_TYPE_SPACE | CHAR_TYPE_PASS))
        ft_tokenizer_advance(tz, 1);

    ft_tokenizer_set_start_pos(tz, tz->current_position);

    // Verifica si llegó al final del texto
    if (ft_tokenizer_istype(tz, CHAR_TYPE_END_OF_TEXT))
    {
        return ft_token_copy(&tz->token_data->defined_tokens[TOKEN_END_TOKEN]);
    }

    index = ft_tokenizer_isdefined_token(tz, FOREACH_ADVANCE_ITERATOR);
    if (index != TYPE_NONE)
    {
        if (index == TYPE_ERROR)
        {
            return NULL;
        }
        return ft_token_copy(&tz->token_data->defined_tokens[index]);
    }

    return NULL;
}


t_token *ft_tokenizer_get_next_token(t_tokenizer *tz)
{
    t_token *token;
    t_character_type quote_type;
    int index;

    // Primero maneja tokens definidos
    token = ft_tokenizer_handle_defined_token(tz);
    if (token != NULL)
    {
        return token;
    }

    while (!ft_tokenizer_istype(tz, CHAR_TYPE_END_OF_TEXT | CHAR_TYPE_SPACE | CHAR_TYPE_PASS | CHAR_TYPE_ERROR))
    {
        // Maneja las secuencias de escape
        if (ft_tokenizer_istype(tz, CHAR_TYPE_BACKSLASH))
        {
            ft_tokenizer_advance(tz, 1);
            if (ft_tokenizer_istype(tz, CHAR_TYPE_END_OF_TEXT) && ft_tokenizer_error(ERROR_UNKNOWN, tz) == ERROR)
            {
                return NULL;
            }
            ft_tokenizer_advance(tz, 1);
        }

        index = ft_tokenizer_isdefined_token(tz, FOREACH_DO_NOT_ADVANCE_ITERATOR);
        if (index == TOKEN_ERROR)
        {
            return NULL;
        }
        if (index != TOKEN_NONE)
        {
            break;
        }

        // Maneja las comillas
        quote_type = ft_tokenizer_isquote(tz); // Debe devolver un tipo de carácter adecuado
        if (quote_type != CHAR_TYPE_NONE)
        {
            if (ft_tokenizer_pass_quotes(tz, quote_type) == ERROR)
                return NULL;
        }
    }

    // Retorna el token encontrado
    return ft_tokenizer_token_grabber(tz, TOKEN_WORD);
}
