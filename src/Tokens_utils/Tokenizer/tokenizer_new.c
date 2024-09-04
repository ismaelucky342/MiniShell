#include "../../../includes/minishell.h"

t_tokenizer			*ft_tokenizer_new(int sloc)
{
	t_tokenizer		*tz;

	tz = mmalloc(sizeof(t_tokenizer));

	if (ft_tokenizer_refill_line(tz, sloc) == ERROR)
	{
		ft_tokenizer_delete(&tz);
		return (NULL);
	}
	return (tz);
}