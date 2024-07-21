# include "minishell.h"

void ft_rlist_cleanup(t_redir *redir_list)
{
    t_redir *ptr;

    while (redir_list)
    {
        ptr = redir_list;
        redir_list = redir_list->next;
        free(ptr->value); 
        free(ptr); 
    }
}
