#include "../../includes/minishell.h"

void			token__del(t_token **token)
{
	if (*token)
	{
		mfree((void **)&(*token)->value);
		mfree((void **)token);
	}
}
