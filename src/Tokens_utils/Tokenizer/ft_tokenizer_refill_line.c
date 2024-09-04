#include "../../../includes/minishell.h"

int				ft_tokenizer_refill_line(t_tokenizer *tz, int sloc)
{
	mfree((void **)&tz->current_line);
	print_prompt(sloc);
	while (!(tz->current_line = get_next_line_v2()) || g_reset == 1)
	{
		g_reset = 0;
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