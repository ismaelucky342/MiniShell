# include "../../includes/minishell.h"

t_ast_node	*ft_node_new(t_ast_node_type type)
{
	t_ast_node		*new;

	new = mmalloc(sizeof(t_ast_node));
	new->type = type;
	new->stdin = STDIN_FILENO;
	new->stdout = STDOUT_FILENO;
	return (new);
}