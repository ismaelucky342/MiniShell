/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/20 17:19:53 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_find_env_index(char **envp, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (envp && envp[i])
	{
		j = 0;
		while (envp[i][j] && key[j] && (envp[i][j] == key[j]))
			++j;
		if (!key[j] && (envp[i][j] == '=' || !envp[i][j]))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_remove_env(t_minishell *sack, char *key)
{
	int	index;
	int	i;

	index = ft_find_env_index(sack->envp, key);
	if (index == -1)
		return (-1);
	free(sack->envp[index]);
	sack->env_elems--;
	i = index;
	while (sack->envp[i])
	{
		sack->envp[i] = sack->envp[i + 1];
		i++;
	}
	return (0);
}
