/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:49:10 by sacorder          #+#    #+#             */
/*   Updated: 2024/09/22 12:25:10 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit;

static int	ft_init_envp(t_minishell *sack, char **envp)
{
	int	ctr;

	ctr = -1;
	g_exit = 0;
	while (envp && envp[sack->env_elems])
		sack->env_elems++;
	sack->env_size = sack->env_elems * 2;
	if (sack->env_size > INT_MAX)
		sack->env_size = INT_MAX;
	else if (sack->env_size == 0)
		sack->env_size = 32;
	sack->envp = ft_calloc(sack->env_size, sizeof(char *));
	if (!sack->envp)
		return (1);
	while (++ctr < sack->env_elems)
		sack->envp[ctr] = ft_strdup(envp[ctr]);
	return (0);
}

static void	ft_fill_envp(t_minishell *sack)
{
	char	*tmp;
	char	*tmp2;
	int		shllvl;

	shllvl = 1 + ft_atoi(get_value_from_env(sack->envp, "SHLVL", NULL));
	if (shllvl >= 1000)
		ft_tmp(&tmp, &shllvl);
	tmp = ft_itoa(shllvl);
	tmp2 = ft_strjoin("SHLVL=", tmp);
	ft_env_build(sack, tmp2);
	free(tmp);
	free(tmp2);
	tmp = get_cwd_str();
	if (tmp)
	{
		tmp2 = ft_strjoin("PWD=", tmp);
		ft_env_build(sack, tmp2);
		free(tmp);
		free(tmp2);
	}
	ft_env_build(sack, "?=0");
}

void	init_minishell(t_minishell *sack, char **envp, int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Minishell: no args supported", STDERR_FILENO);
		exit(1);
	}
	ft_bzero(sack, sizeof(t_minishell));
	if (ft_init_envp(sack, envp))
	{
		ft_putendl_fd("Minishell: error allocating envp space", STDERR_FILENO);
		ft_memory_error(sack);
	}
	ft_fill_envp(sack);
	sack->cmd_tree = NULL;
	sack->ft_prompt = ft_prompt(sack->envp);
	ft_set_signal_handlers();
	ft_init_file(sack);
	ft_h_fill(sack);
}
