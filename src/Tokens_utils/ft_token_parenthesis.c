#include "../../includes/minishell.h"

int				token__isparenthesis(t_token *token)
{
	return (token__istype(token, CHAR_TYPE_LEFT_PARENTHESIS | CHAR_TYPE_RIGHT_PARENTHESIS));
}