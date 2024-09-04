#include "../../includes/minishell.h"

void ft_node_delete(t_ast_node **node, int opt)
{
    if (node == NULL || *node == NULL)
        return;
    
    ft_token_list_del(&(*node)->av);
    ft_token_list_del(&(*node)->redirections);
    ft_token_list_del(&(*node)->separators);
    
    if (opt == CLEAN_NODE_AND_CHILDS)
    {
        if ((*node)->left != NULL)
            ft_node_delete(&(*node)->left, opt);
        if ((*node)->right != NULL)
            ft_node_delete(&(*node)->right, opt);
    }
    
    mfree((void **)node);
}
