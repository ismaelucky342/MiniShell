/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_refill_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:23:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 11:41:53 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int				ft_tokenizer_refill_line(t_tokenizer *tz, int sloc, t_global_state *state)
{
	mfree((void **)&tz->current_line);
	print_prompt(sloc);
	while (!(tz->current_line = get_next_line_v2()) || state->reset == 1)
	{
		state->reset = 0;
		if (!tz->current_line && ft_tokenizer_error(ERROR_GET_NEXT_LINE, tz) == ERROR)
			return (ERROR);
	}
	tz->current_position = 0;
	tz->start_index= 0;
	tz->line_length = ft_strlen(tz->current_line);
	tz->current_char = tz->current_line[tz->current_position];
	tz->line_start_char= tz->current_line[tz->start_index];
	return (SUCCESS);
}
