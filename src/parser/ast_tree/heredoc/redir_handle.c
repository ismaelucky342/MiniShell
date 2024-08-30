#include "../include/minishell.h"

int redir_handler(t_redir *redir)
{
    int i = 0;
    t_cmd *cmd = redir->redirects;

    while (cmd->redirects[i])
    {
        if (cmd->redirect_type[i] >= 3)
        {
            cmd->redirects[i] = expander(cmd->redirects[i]); // sigo necesitando esto dani
            if (cmd->redirect_type[i] == 4)
                cmd->redirect_type[i] = heredoc(cmd->redirects[i]);
            else
                cmd->redirect_type[i] = -heredoc(cmd->redirects[i]);
            free(cmd->redirects[i]);
            cmd->redirects[i] = NULL;
            if (cmd->redirect_type[i] == -1)
                return (-1);
        }
        i++;
    }
    if (redir->next)
        climb_tree(redir->next, redir->type);
    return (0);
}
