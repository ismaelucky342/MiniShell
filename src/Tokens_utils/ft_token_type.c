#include "../../includes/minishell.h"

int				ft_token_istype(t_token *token, t_token_type_key type)
{
	return (type & token->type);
}

int				ft_token_iseot(t_token *token)
{
	return (ft_token_istype(token, TOKEN_END_TOKEN));
}

int				ft_token_isword(t_token *token)
{
	return (ft_token_istype(token, TOKEN_WORD));
}

int				ft_token_issep(t_token *token)
{
	return (ft_token_istype(token, TOKEN_SEMICOLON | TOKEN_LOGICAL_AND | TOKEN_LOGICAL_OR | TOKEN_PIPE));
}

int				ft_token_isredir(t_token *token)
{
	return (ft_token_istype(token, TOKEN_REDIR_INPUT | TOKEN_REDIR_OUTPUT | TOKEN_DBL_REDIR_OUTPUT));
}