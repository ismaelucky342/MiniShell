/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:54:02 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:35:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	quote_as_token(t_tokenizer *tz, t_character_type *search)
{
	*search = ft_tokenizer_isquote(tz);
	if (*search != CHAR_NONE)
		ft_tokenizer_pass_quotes(tz, *search);
	ft_tokenizer_advance(tz, 1);
}

t_token	*ft_tokenizer_handle_defined_token(t_tokenizer *tz, t_mem_context *ctx)
{
	int	index;

	while (ft_tokenizer_istype(tz, CHAR_SPACE | CHAR_PASS))
		ft_tokenizer_advance(tz, 1);
	ft_tokenizer_set_start_pos(tz, tz->current_position);
	if (ft_tokenizer_istype(tz, CHAR_END_OF_TEXT))
	{
		return (ft_token_copy(&g_defined_tokens[TOKEN_END_TOKEN], ctx));
	}
	index = ft_isdefined_token(tz, FOREACH_ADVANCE_ITERATOR);
	if (index != TYPE_NONE)
	{
		if (index == TYPE_ERROR)
		{
			return (NULL);
		}
		return (ft_token_copy(&g_defined_tokens[index], ctx));
	}
	return (NULL);
}

t_token	*ft_tokenizer_get_next_token_part2(t_tokenizer *tz, t_mem_context *ctx)
{
	t_character_type	quote_type;
	int					index;

	while (!ft_tokenizer_istype(tz,
			CHAR_END_OF_TEXT | CHAR_SPACE | CHAR_PASS | CHAR_ERROR))
	{
		if (ft_tokenizer_istype(tz, CHAR_BACKSLASH))
		{
			ft_tokenizer_advance(tz, 1);
			if (ft_tokenizer_istype(tz, CHAR_END_OF_TEXT)
				&& ft_tokenizer_error(ERROR_UNKNOWN, tz) == ERROR)
				return (NULL);
			ft_tokenizer_advance(tz, 1);
		}
		index = ft_isdefined_token(tz, FOREACH_DO_NOT_ADVANCE_ITERATOR);
		if (index == TOKEN_ERROR)
			return (NULL);
		if (index != TOKEN_NONE)
			break ;
		quote_type = ft_tokenizer_isquote(tz);
		if (quote_type != CHAR_NONE)
			if (ft_tokenizer_pass_quotes(tz, quote_type) == ERROR)
				return (NULL);
	}
	return (ft_tokenizer_token_grabber(tz, TOKEN_WORD, ctx));
}

t_token	*ft_tokenizer_get_next_token(t_tokenizer *tz, t_mem_context *ctx)
{
	t_token	*token;

	token = ft_tokenizer_handle_defined_token(tz, ctx);
	if (token != NULL)
		return (token);
	return (ft_tokenizer_get_next_token_part2(tz, ctx));
}
