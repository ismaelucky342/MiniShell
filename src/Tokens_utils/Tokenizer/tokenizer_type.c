/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:52:23 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 12:32:46 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_tokenizer_istype(t_tokenizer *tz, t_character_type type)
{
	return (type & g_token_dictionary[(int)(tz->current_char)]);
}

int	ft_tokenizer_istype_start(t_tokenizer *tz, t_character_type type)
{
	return (type & g_token_dictionary[(int)(tz->start_index)]);
}

char	ft_tokenizer_peek(t_tokenizer *tz)
{
	if (tz->current_position + 1 < tz->line_length)
	{
		return (tz->current_line[tz->current_position + 1]);
	}
	return ('\0');
}

int	ft_tokenizer_isword(t_tokenizer *tz)
{
	return (ft_tokenizer_istype(tz,
			CHAR_TYPE_WORD | CHAR_TYPE_SINGLE_QUOTE
			| CHAR_TYPE_DOUBLE_QUOTE | CHAR_TYPE_BACKSLASH));
}

int	ft_tokenizer_isquote(t_tokenizer *tz)
{
	return (ft_tokenizer_istype(tz,
			CHAR_TYPE_SINGLE_QUOTE | CHAR_TYPE_DOUBLE_QUOTE));
}
