/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:40:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/02 22:36:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* @brief Extracts the value of an environment variable from a given entry.
*

* Compares an environment entry (`env_entry`) to a key (`key`)
to determine
* ​​if it corresponds to an environment variable. If there is a match,
a pointer

* to the associated value is returned and the existence of the variable is marked.
If there is no match,
* NULL is returned.
*
* @param env_entry Environment entry being evaluated.
* @param key Key of the environment variable to search for.

* @param exists Pointer to an integer that is set to 1
if the variable exists,
* or unchanged if the variable is not found.
* @return char* Pointer to the value of the environment variable if it exists,
NULL otherwise.
*/
static char	*extract_value(char *env_entry, char *key, int *exists)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (!ft_strncmp(env_entry, key, key_len) && env_entry[key_len] == '=')
	{
		if (exists)
			*exists = 1;
		return (env_entry + key_len + 1);
	}
	return (NULL);
}

/**

* @brief Gets the value of an environment variable from an array of environment entries.

*

* Iterates through an array of pointers to strings (`envp`) looking for a specific key
* (`key`). Calls `extract_value` to determine if an entry in `envp`
* matches the key. If found,
the associated value is returned; if not,
* the variable is indicated as not existing.
*

* @param envp Array of pointers to strings representing environment variables.
* @param key Key of the environment variable whose value is being searched for.

* @param exists Pointer to an integer that is set to 1 if the variable
* exists, or 0 if not found.
* @return char* Value of the environment variable if found, empty string
* if not.
*/
char	*get_value_from_env(char **envp, char *key, int *exists)
{
	char	*value;
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		value = extract_value(envp[i], key, exists);
		if (value)
			return (value);
		i++;
	}
	if (exists)
		*exists = 0;
	return ("");
}
