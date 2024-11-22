/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:42:45 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/22 14:14:13 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** 
* @brief Increases the size of the minishell environment by allocating more memory.
* * This function reallocates space for the array of string pointers that * represents the minishell's environment variables (`envp`). If the actual size * plus 32 exceeds the integer limit, an error is returned.
* If the reallocation is successful, the existing values ​​are copied to the * new memory and the old memory is freed.
* 
* @param boogeyman Pointer to the `t_minishell` structure containing the * state of the minishell, including the environment and its size.
* @return int Returns `OK` if the reallocation was successful, `KO` on * error.
*/
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

/**
* @brief Adds a new entry to the minishell environment.
*
* This function duplicates the string `key_val` and stores it in the array of
* `envp` pointers at the position corresponding to the current number of elements
* (`env_elems`). Increments the environment element counter.
*
* @param boogeyman Pointer to the `t_minishell` structure containing the
* state of the minishell.
* @param key_val String representing the new environment variable to add.
*/
static void	ft_entry(t_minishell *boogeyman, char *key_val)
{
	boogeyman->envp[boogeyman->env_elems] = ft_strdup(key_val);
	boogeyman->env_elems++;
}

/**
* @brief Replaces an existing entry in the minishell environment.
*
* Looks for the matching entry in the `envp` array and, if found,
* frees the memory of the old entry and replaces it with a new one
* that corresponds to `key_val`.
*
* @param envp Array of string pointers representing environment variables.
* @param key_val New string to use to replace the entry.
* @param key String used to look up the existing entry in `envp`.
*/
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

/**
* @brief Adds a new environment variable to the minishell.
*
* This function checks if there is room in the environment for a new entry.
* If there is not enough room, it calls `ft_env_realloc` to increase the
* size. Then, `ft_entry` is called to add the new variable to the
* environment.
*
* @param boogeyman Pointer to the `t_minishell` structure containing the
* state of the minishell.
* @param key_val String representing the new environment variable to add.
* @return int Returns `OK` if the operation was successful, `KO` on error.
*/
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

/**
* @brief Constructs or updates an environment variable in the minishell.
*
* This function checks whether `key_val` contains an equal sign to determine
* ​​whether to create or update an environment variable. If the variable already
* exists and needs to be updated, `ft_replace_entry` is called. If it does not
* exist, `ft_new_env` is called to create a new entry.
*
* @param boogeyman Pointer to the `t_minishell` structure containing the
* state of the minishell.
* @param key_val String representing the new environment variable to be
* built or updated.
* @return int Always returns `OK`.
*/
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
