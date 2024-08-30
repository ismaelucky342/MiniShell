#include "../includes/minishell.h"

int handle_cmd(t_cmd *cmd)
{
    int i = 0;

    while (cmd->redir[i])
    {
        if (cmd->redir_type[i] >= 3)
        {
            cmd->redir[i] = expander(cmd->redir[i]); // necesito el expander dani
            if (cmd->redir_type[i] == 4)
                cmd->redir_type[i] = heredoc(cmd->redir[i]);
            else
                cmd->redir_type[i] = -heredoc(cmd->redir[i]);
            free(cmd->redir[i]);
            cmd->redir[i] = NULL;
            if (cmd->redir_type[i] == -1)
                return (-1);
        }
        i++;
    }
    return (0);
}
