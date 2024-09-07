#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"

/*-----------RETURN SIGNAL-------------*/

typedef enum return_signal
{
	CONTINUE,
	NOMATCH
}					t_return_signal;

/*-----------SIGNALS STRUCTURE---------*/

typedef struct s_signal_context
{
	unsigned int		exit_status;
	int					reset_flag;
	t_hashtable			*env_hashtable;
}						t_signal_context;

extern t_signal_context	g_signals;

void					sig_handler(int signo);
void					init_signal_context(t_signal_context *context);

#endif
