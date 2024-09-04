#include "../../../includes/minishell.h"

void    ft_tokenizer_delete(t_tokenizer **tz)
{
	if (*tz)
	{
		mfree((void **)&(*tz)->current_line);
		mfree((void **)tz);
	}
}
