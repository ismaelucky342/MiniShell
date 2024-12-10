/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:49:10 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/10 20:30:13 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_is_exec;

static int	ft_init_envp(t_mini *boogeyman, char **envp)
{
	int	ctr;

	ctr = -1;
	g_is_exec = 0;
	while (envp && envp[boogeyman->env_elems])
		boogeyman->env_elems++;
	boogeyman->env_size = boogeyman->env_elems * 2;
	if (boogeyman->env_size > INT_MAX)
		boogeyman->env_size = INT_MAX;
	else if (boogeyman->env_size == 0)
		boogeyman->env_size = 32;
	boogeyman->envp = ft_calloc(boogeyman->env_size, sizeof(char *));
	if (!boogeyman->envp)
		return (1);
	while (++ctr < boogeyman->env_elems)
		boogeyman->envp[ctr] = ft_strdup(envp[ctr]);
	return (0);
}

static void	ft_fill_envp(t_mini *boogeyman)
{
	char	*tmp;
	char	*tmp2;
	int		shllvl;

	shllvl = 1 + ft_atoi(ft_get_from_env(boogeyman->envp, "SHLVL", NULL));
	if (shllvl >= 1000)
		tmp_management(&tmp, &shllvl);
	tmp = ft_itoa(shllvl);
	tmp2 = ft_strjoin("SHLVL=", tmp);
	ft_add_to_env(boogeyman, tmp2);
	freedom((void **)&tmp);
	tmp = cwd_str_status();
	if (tmp)
		boogeyman->aux_pwd = tmp;
	boogeyman->rvalue = 0;
}

/*
	Initializes main struct,
	custom envp (allocation and copy of given envp,
	plus setting of varibles such as SHLVL),
	creates a custom prompt, sets signal handling 
	and creates persistent history file if posible
*/
void	init(t_mini *boogeyman, char **envp, int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("MiniShell: no args supported", STDERR_FILENO);
		exit(1);
	}
	ft_bzero(boogeyman, sizeof(t_mini));
	if (ft_init_envp(boogeyman, envp))
	{
		ft_putendl_fd("MiniShell: error allocating envp space", STDERR_FILENO);
		ft_memory_err_exit(boogeyman);
	}
	ft_fill_envp(boogeyman);
	boogeyman->cmd_tree = NULL;
	boogeyman->custom_prompt = ft_prompt(boogeyman->envp);
	signal(SIGINT, ft_signals);
	signal(SIGQUIT, ft_signals);
	ft_set_signal_print(0);
	ft_init_history_file(boogeyman);
	ft_history_filler(boogeyman);
}
