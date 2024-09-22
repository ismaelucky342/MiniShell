/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:42:45 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:40:21 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_env_realloc(t_minishell *sack)
{
	char	**new_envp;
	char	**src;

	if (sack->env_size + 32 < INT_MAX)
		sack->env_size += 32;
	else
		return (1);
	new_envp = ft_calloc(sack->env_size, sizeof(char *));
	if (!new_envp)
		return (1);
	src = sack->envp;
	while (*src)
	{
		*new_envp++ = *src++;
	}
	free(sack->envp);
	sack->envp = new_envp - (src - sack->envp);
	return (0);
}

static void	ft_entry(t_minishell *sack, char *key_val)
{
	sack->envp[sack->env_elems] = ft_strdup(key_val);
	sack->env_elems++;
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

static int	ft_new_env(t_minishell *sack, char *key_val)
{
	if (sack->env_elems + 1 >= sack->env_size)
	{
		if (ft_env_realloc(sack))
		{
			ft_putendl_fd("Minishell: couldn't add more envp tuples",
				STDERR_FILENO);
			ft_memory_error(sack);
			return (1);
		}
	}
	ft_entry(sack, key_val);
	return (0);
}

int	ft_env_build(t_minishell *sack, char *key_val)
{
	char	*key;
	int		exists;

	if (ft_strchr(key_val, '='))
		key = ft_substr(key_val, 0, ft_strchr(key_val, '=') - key_val);
	else
		key = ft_strdup(key_val);
	get_value_from_env(sack->envp, key, &exists);
	if (exists && ft_strchr(key_val, '='))
		ft_replace_entry(sack->envp, key_val, key);
	else if (!exists)
		ft_new_env(sack, key_val);
	free(key);
	return (0);
}
