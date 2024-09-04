#include "../../includes/minishell.h"

void			ft_token_del(t_token **token)
{
	if (*token)
	{
		mfree((void **)&(*token)->value);
		mfree((void **)token);
	}
}
