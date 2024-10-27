/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:42:45 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:27:49 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_env_realloc(t_minishell *boogeyman)
{
	char	**new_envp;
	char	**src;

	if (boogeyman->env_size + 32 < INT_MAX)
		boogeyman->env_size += 32;
	else
		return (KO);
	new_envp = ft_calloc(boogeyman->env_size, sizeof(char *));
	if (!new_envp)
		return (KO);
	src = boogeyman->envp;
	while (*src)
	{
		*new_envp++ = *src++;
	}
	free(boogeyman->envp);
	boogeyman->envp = new_envp - (src - boogeyman->envp);
	return (OK);
}

static void	ft_entry(t_minishell *boogeyman, char *key_val)
{
	boogeyman->envp[boogeyman->env_elems] = ft_strdup(key_val);
	boogeyman->env_elems++;
}

static void	ft_replace_entry(char **envp, char *key_val, char *key)
{
	char	**current;

	current = envp;
	while (*current)
	{
		if (!ft_strncmp(*current, key, ft_strlen(key)))
		{
			free(*current);
			*current = ft_strdup(key_val);
			break ;
		}
		current++;
	}
}

static int	ft_new_env(t_minishell *boogeyman, char *key_val)
{
	if (boogeyman->env_elems + 1 >= boogeyman->env_size)
	{
		if (ft_env_realloc(boogeyman))
		{
			ft_putendl_fd("Minishell: couldn't add more envp tuples",
				STDERR_FILENO);
			ft_memory_error(boogeyman);
			return (KO);
		}
	}
	ft_entry(boogeyman, key_val);
	return (OK);
}

int	ft_env_build(t_minishell *boogeyman, char *key_val)
{
	char	*key;
	int		exists;

	if (ft_strchr(key_val, '='))
		key = ft_substr(key_val, 0, ft_strchr(key_val, '=') - key_val);
	else
		key = ft_strdup(key_val);
	get_value_from_env(boogeyman->envp, key, &exists);
	if (exists && ft_strchr(key_val, '='))
		ft_replace_entry(boogeyman->envp, key_val, key);
	else if (!exists)
		ft_new_env(boogeyman, key_val);
	free(key);
	return (OK);
}
