/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:48:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 10:56:43 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Reallocates the environment array and adds a new environment variable.
 *
 * This function reallocates the environment array to increase its size by 32
 * and adds a new environment variable to the array.
 *
 * @param boogeyman Pointer to the t_minishell structure.
 * @param passkey The new environment variable to add.
 * @return int Returns 0 on success, 1 on failure.
 */
static int	ft_realloc_and_add_envp(t_minishell *boogeyman, char *passkey)
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
	res[ctr] = ft_strdup(passkey);
	boogeyman->env_elems++;
	free(boogeyman->envp);
	boogeyman->envp = res;
	return (0);
}

/**
 * @brief Searches for an environment variable and replaces it if found.
 *
 * This function searches for an environment variable in the given array and
 * replaces it with the provided passkey if found.
 *
 * @param envp The environment array.
 * @param passkey The new environment variable to replace with.
 * @param key The key to search for in the environment array.
 */

static void	ft_search_and_replace_env(char **envp, char *passkey, char *key)
{
	int		i;

	i = -1;
	while (envp && envp[++i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			if (envp[i][ft_strlen(key)] == '='
				|| !envp[i][ft_strlen(key)])
			{
				free(envp[i]);
				envp[i] = ft_strdup(passkey);
				break ;
			}
		}
	}
}

/**
 * @brief Adds a new environment variable to the environment array.
 *
 * This function adds a new environment variable to the environment array. If
 * the array is full, it reallocates the array to increase its size.
 *
 * @param boogeyman Pointer to the t_minishell structure.
 * @param passkey The new environment variable to add.
 * @return int Returns 0 on success, 1 on failure.
 */
static int	ft_add_env_new(t_minishell *boogeyman, char *passkey)
{
	if (boogeyman->env_elems + 1 < boogeyman->env_size)
	{
		boogeyman->envp[boogeyman->env_elems] = ft_strdup(passkey);
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
 * @brief Adds or updates an environment variable in the environment array.
 *
 * This function adds a new environment variable to the environment array or
 * updates an existing one if it already exists.
 *
 * @param boogeyman Pointer to the t_minishell structure.
 * @param passkey The environment variable to add or update.
 * @return int Returns 0 on success, 1 on failure.
 */
int	ft_add_to_env(t_minishell *boogeyman, char *passkey)
{
	char	*key;
	int		exists;

	exists = 0;
	if (ft_strchr(passkey, '='))
		key = ft_substr(passkey, 0, ft_strchr(passkey, '=') - passkey);
	else
		key = ft_strdup(passkey);
	if ((!ft_strncmp(ft_get_from_env(boogeyman->envp, key, &exists), "", 1)
			&& exists && ft_strchr(passkey, '='))
		|| (exists && ft_strchr(passkey, '=')))
		ft_search_and_replace_env(boogeyman->envp, passkey, key);
	else if (!exists)
	{
		if (ft_add_env_new(boogeyman, passkey))
		{
			free(key);
			return (1);
		}
	}
	free(key);
	return (0);
}
