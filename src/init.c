/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:50:36 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 23:02:25 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern int	g_exit;

static int	ft_init_envp(t_minishell *boogeyman, char **envp)
{
	int	ctr;

	ctr = -1;
	g_exit = 0;
	while (envp && envp[boogeyman->env_elems])
		boogeyman->env_elems++;
	boogeyman->env_size = boogeyman->env_elems * 2;
	if (boogeyman->env_size > INT_MAX)
		boogeyman->env_size = INT_MAX;
	else if (boogeyman->env_size == 0)
		boogeyman->env_size = 32;
	boogeyman->envp = ft_calloc(boogeyman->env_size, sizeof(char *));
	if (!boogeyman->envp)
		return (KO);
	while (++ctr < boogeyman->env_elems)
		boogeyman->envp[ctr] = ft_strdup(envp[ctr]);
	return (OK);
}

static void	ft_fill_envp(t_minishell *boogeyman)
{
	char	*tmp;
	char	*tmp2;
	int		chell;

	chell = 1 + ft_atoi(get_value_from_env(boogeyman->envp, "SHLVL", NULL));
	if (chell >= 1000)
		ft_tmp(&tmp, &chell);
	tmp = ft_itoa(chell);
	tmp2 = ft_strjoin("SHLVL=", tmp);
	ft_env_build(boogeyman, tmp2);
	free(tmp);
	free(tmp2);
	tmp = get_cwd_str();
	if (tmp)
	{
		tmp2 = ft_strjoin("PWD=", tmp);
		ft_env_build(boogeyman, tmp2);
		free(tmp);
		free(tmp2);
	}
	ft_env_build(boogeyman, "?=0");
}

void	init_minishell(t_minishell *boogeyman, char **envp, int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Minishell: no args supported", STDERR_FILENO);
		exit(1);
	}
	ft_bzero(boogeyman, sizeof(t_minishell));
	if (ft_init_envp(boogeyman, envp))
	{
		ft_putendl_fd("Minishell: error allocating envp space", STDERR_FILENO);
		ft_memory_error(boogeyman);
	}
	ft_fill_envp(boogeyman);
	boogeyman->cmd_tree = NULL;
	boogeyman->ft_prompt = ft_prompt(boogeyman->envp);
	ft_set_signal_handlers();
	ft_init_file(boogeyman);
	ft_h_fill(boogeyman);
}
