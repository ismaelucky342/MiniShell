#include "../../includes/minishell.h"

int				token__istype(t_token *token, t_token_type_key type)
{
	return (type & token->type);
}

int				token__iseot(t_token *token)
{
	return (token__istype(token, TOKEN_END_TOKEN));
}

int				token__isword(t_token *token)
{
	return (token__istype(token, TOKEN_WORD));
}

int				token__issep(t_token *token)
{
	return (token__istype(token, TOKEN_SEMICOLON | TOKEN_LOGICAL_AND | TOKEN_LOGICAL_OR | TOKEN_PIPE));
}

int				token__isredir(t_token *token)
{
	return (token__istype(token, TOKEN_REDIR_INPUT | TOKEN_REDIR_OUTPUT | TOKEN_DBL_REDIR_OUTPUT));
}