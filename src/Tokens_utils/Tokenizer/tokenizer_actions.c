/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:41:08 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:29:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_tokenizer_advance(t_tokenizer *tz, int n)
{
	if (tz->current_char == CHAR_END_OF_TEXT)
		return (0);
	tz->previous_char = tz->current_char;
	tz->current_position += 1;
	if (tz->current_position > tz->line_length - 1)
	{
		tz->current_char = CHAR_END_OF_TEXT;
		return (0);
	}
	else
	{
		tz->current_char = tz->current_line[tz->current_position];
		if (n - 1 > 0)
			return (ft_tokenizer_advance(tz, n - 1));
		else
			return (1);
	}
}

void	ft_tokenizer_advance_foreach(t_tokenizer *tz, t_character_type type,
		int whis)
{
	while (1)
	{
		if (ft_tokenizer_istype(tz, CHAR_BACKSLASH)
			&& type == CHAR_WORD)
			ft_tokenizer_advance(tz, 1);
		else if (ft_tokenizer_istype(tz, CHAR_BACKSLASH)
			&& (type == CHAR_DOUBLE_QUOTE
				|| type == CHAR_SINGLE_QUOTE)
			&& whis == FOREACH_WHILE_CONDITION_FALSE)
			ft_tokenizer_advance(tz, 1);
		if (!ft_tokenizer_advance(tz, 1))
			break ;
		if (whis == FOREACH_WHILE_CONDITION_FALSE)
		{
			if (ft_tokenizer_istype(tz, type))
				break ;
		}
		else
		{
			if (!ft_tokenizer_istype(tz, type))
				break ;
		}
	}
}

int	ft_tokenizer_pass_quotes(t_tokenizer *tz, t_character_type type)
{
	ft_tokenizer_advance(tz, 1);
	while (!ft_tokenizer_istype(tz, type))
	{
		if (ft_tokenizer_istype(tz, CHAR_BACKSLASH))
			ft_tokenizer_advance(tz, 1);
		if (!ft_tokenizer_advance(tz, 1))
			break ;
	}
	if (!ft_tokenizer_istype(tz, type) && ft_tokenizer_error(ERROR_UNKNOWN,
			tz) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	ft_tokenizer_set_start_pos(t_tokenizer *tz, int new_pos)
{
	tz->start_index = new_pos;
	tz->line_start_char = tz->current_line[new_pos];
}

t_token	*ft_tokenizer_token_grabber(t_tokenizer *tz, t_token_type_key type,
		t_mem_context *ctx)
{
	t_token	*new;
	char	*sub_value;

	sub_value = ft_strsub(ctx, tz->current_line, tz->start_index,
			tz->current_position - tz->start_index);
	if (sub_value == NULL)
		return (NULL);
	new = ft_token_new(type, sub_value, tz->start_index, ctx);
	return (new);
}
