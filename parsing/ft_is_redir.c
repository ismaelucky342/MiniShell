#include "minishell.h"

int	ft_is_redir(int token_type)
{
	if (token_type == TOKEN_GREATER || token_type == TOKEN_GREATGREATER || \
		token_type == TOKEN_LESSER || token_type == TOKEN_LESSLESSER)
		return (1);
	return (0);
}