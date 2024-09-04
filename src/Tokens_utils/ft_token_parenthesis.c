#include "../../includes/minishell.h"

int				ft_token_isparenthesis(t_token *token)
{
	return (ft_token_istype(token, CHAR_TYPE_LEFT_PARENTHESIS | CHAR_TYPE_RIGHT_PARENTHESIS));
}