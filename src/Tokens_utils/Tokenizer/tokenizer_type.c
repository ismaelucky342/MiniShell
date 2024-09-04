#include "../../../includes/minishell.h"

int				ft_tokenizer_istype(t_tokenizer tz, t_character_type type)
{
	return (type & g_token_ascii_table[(int)(tz->current_char)]);
}

int				ft_tokenizer_istype_start(t_tokenizer tz, t_character_type type)
{
	return (type & g_token_ascii_table[(int)(tz->start_char)]);
}

char			ft_tokenizer_peek(t_tokenizer tz)
{
	return (tz->current_line[tz->current_position + 1]);
}

int				ft_tokenizer_isword(t_tokenizer tz)
{
	return (ft_tokenizer_istype(tz, CHAR_TYPE_WORD | CHAR_TYPE_SINGLE_QUOTE | CHAR_TYPE_DOUBLE_QUOTE |
		CHAR_TYPE_BACKSLASH));
}

int				ft_tokenizer_isquote(t_tokenizer tz)
{
	return (ft_tokenizer_istype(tz, CHAR_TYPE_SINGLE_QUOTE | CHAR_TYPE_DOUBLE_QUOTE));
}