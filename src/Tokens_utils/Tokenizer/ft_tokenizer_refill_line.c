/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_refill_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:23:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 12:51:30 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_new_line(t_tokenizer *tz, char *new_line)
{
	if (g_reset)
	{
		g_reset = 0;
		mfree((void **)&new_line);
	}
	else if (new_line)
		tz->current_line = new_line;
	else
		if (ft_tokenizer_error(ERROR_GET_NEXT_LINE, tz) == ERROR)
			tz->current_line = NULL;
}

int	ft_tokenizer_refill_line(t_tokenizer *tz, int sloc)
{
	char	*new_line;

	mfree((void **)&tz->current_line);
	print_prompt(sloc);
	while (1)
	{
		new_line = get_next_line_v2();
		handle_new_line(tz, new_line);
		if (tz->current_line != NULL)
			break ;
	}
	tz->current_position = 0;
	tz->start_index = 0;
	tz->line_length = ft_strlen(tz->current_line);
	tz->current_char = tz->current_line[0];
	tz->line_start_char = tz->current_line[0];
	if (tz->current_line != NULL)
		return (SUCCESS);
	else
		return (ERROR);
}
