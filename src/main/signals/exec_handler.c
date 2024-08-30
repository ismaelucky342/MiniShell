#include "minishell.h"

extern int	g_signal;

void	exec_handler(int signal)
{
	g_signal = 1;
    
	if (signal == SIGINT)
		write(STDIN_FILENO, "\n", 1);
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}