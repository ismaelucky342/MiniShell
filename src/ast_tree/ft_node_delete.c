# include "../../includes/minishell.h"

void	node__del(t_ast_node **node, int opt)
{
	ft_token_list_del(&(*node)->av);
	ft_token_list_del(&(*node)->redirections);
	ft_token_list_del(&(*node)->separators);
	if (opt == CLEAN_NODE_AND_CHILDS)
	{
		(*node)->left ? node__del(&(*node)->left, opt) : 0;
		(*node)->right ? node__del(&(*node)->right, opt) : 0;
	}
	mfree((void **)node);
}