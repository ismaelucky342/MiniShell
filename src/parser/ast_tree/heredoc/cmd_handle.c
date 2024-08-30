#include "../includes/minishell.h"

int	cmd_handle(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->redir[i])
	{
		if (cmd->redir_type[i] >= 3)
		{
			cmd->redir[i] = expander(cmd->redir[i]); //dani necesito esto
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