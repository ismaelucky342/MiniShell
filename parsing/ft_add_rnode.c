
#include "../includes/minishell.h"

t_redir	*ft_init_redir_node(int token_type)
{
	t_redir	*redir_node;

	redir_node = malloc(sizeof(t_redir));
	redir_node->value = NULL;
	redir_node->next = NULL;
	if (token_type == TOKEN_GREATER)
		redir_node->redir_type = REDIR_OUT;
	if (token_type == TOKEN_GREATGREATER)
		redir_node->redir_type = REDIR_APPEND_OUT;
	if (token_type == TOKEN_LESSER)
		redir_node->redir_type = REDIR_IN;
	if (token_type == TOKEN_LESSLESSER)
		redir_node->redir_type = REDIR_HEREDOC;
	return (redir_node);
}
