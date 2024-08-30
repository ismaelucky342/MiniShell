#include "minishell.h"


void	parse_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDIN_FILENO, "^C\n", 3);
		if (!DEBUG)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if (signal == SIGQUIT)

}