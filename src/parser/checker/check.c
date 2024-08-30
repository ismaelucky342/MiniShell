#include "parser.h"

int	is_operator(t_token_type type)
{
	return (type == T_AND || type == T_OR);
}

int	is_variable(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_redirect(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_REDIR_HEREDOC);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}