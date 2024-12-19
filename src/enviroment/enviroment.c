/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:48:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/18 17:44:39 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Reallocates the env array and adds a new env variable.
 *
 * This function reallocates the env array to increase its size by 32
 * and adds a new env variable to the array.
 *
 * @param boogeyman Pointer to the t_mini structure.
 * @param passkey The new env variable to add.
 * @return int Returns 0 on success, 1 on failure.
 */
static int	ft_realloc_and_add_envp(t_mini *boogeyman, char *passkey)
{
	char	**res;
	int		ctr;

	ctr = -1;
	if (boogeyman->env_size + 32 < INT_MAX)
		boogeyman->env_size += 32;
	else
		return (1);
	res = ft_calloc(boogeyman->env_size, sizeof(char *));
	if (!res)
		return (1);
	while (boogeyman->envp[++ctr])
		res[ctr] = boogeyman->envp[ctr];
	res[ctr] = passkey;
	boogeyman->env_elems++;
	freedom((void **)&boogeyman->envp);
	boogeyman->envp = res;
	return (0);
}

/**
 * @brief Searches for an env variable and replaces it if found.
 *
 * This function searches for an env variable in the given array and
 * replaces it with the provided passkey if found.
 *
 * @param envp The env array.
 * @param passkey The new env variable to replace with.
 * @param key The key to search for in the env array.
 */
void	ft_search_and_replace_env(char **envp, char *passkey, char *key)
{
	int		i;

	i = -1;
	while (envp && envp[++i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			if (envp[i][ft_strlen(key)] == '=' || !envp[i][ft_strlen(key)])
			{
				free(envp[i]);
				envp[i] = passkey;
				return ;
			}
		}
	}
	freedom((void **)&passkey);
}

/**
 * @brief Adds a new env variable to the env array.
 *
 * This function adds a new env variable to the env array. If
 * the array is full, it reallocates the array to increase its size.
 *
 * @param boogeyman Pointer to the t_mini structure.
 * @param passkey The new env variable to add.
 * @return int Returns 0 on success, 1 on failure.
 */
static int	ft_add_env_new(t_mini *boogeyman, char *passkey)
{
	if (boogeyman->env_elems + 1 < boogeyman->env_size)
	{
		boogeyman->envp[boogeyman->env_elems] = passkey;
		boogeyman->env_elems += 1;
	}
	else
	{
		if (ft_realloc_and_add_envp(boogeyman, passkey))
		{
			ft_putendl_fd("MiniShell: couldn't add more envp tuples",
				STDERR_FILENO);
			ft_memory_err_exit(boogeyman);
		}
	}
	return (0);
}

/**
 * @brief Adds or updates an env variable in the env array.
 *
 * This function adds a new env variable to the env array or
 * updates an existing one if it already exists.
 *
 * @param boogeyman Pointer to the t_mini structure.
 * @param passkey The env variable to add or update.
 * @return int Returns 0 on success, 1 on failure.
 */
int	ft_add_to_env(t_mini *boogeyman, char *passkey)
{
	char	*key;
	int		exists;

	exists = 0;
	if (ft_strchr(passkey, '='))
		key = ft_substr(passkey, 0, ft_strchr(passkey, '=') - passkey);
	else
		key = ft_strdup(passkey);
	if (!key)
		return (1);
	if ((!ft_strncmp(ft_get_env_var(boogeyman->envp, key, &exists), "", 1)
			&& exists && ft_strchr(passkey, '=')) || (exists
			&& ft_strchr(passkey, '=')))
		ft_search_and_replace_env(boogeyman->envp, passkey, key);
	else if (!exists)
		if (ft_add_env_new(boogeyman, passkey))
			return (freedom((void **)&key), freedom((void **)&passkey), 1);
	return (freedom((void **)&key), 0);
}
