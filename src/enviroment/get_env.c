/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:55:51 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:39:10 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_get_from_env
	- Retrieves the value associated with a given key from the
		env variables.
 * @param envp: The env variables array.
 * @param key: The key to search for in the env variables.
 * @param exists: Pointer to an integer that will be set to 1 if the key exists,
	otherwise 0.
 *
 * This function first checks if the key is an empty string or
		a single dollar sign.
 * If the key is an empty string, it returns "$".
 * If the key is a single dollar sign, it returns "Minishell: not a valid id".
 * Otherwise,
	it calls get_val_from_env to retrieve the value associated with the key.
 *
 * Return: The value associated with the key,
	or an appropriate message if the key is invalid.
 */
char	*ft_get_from_env(char **envp, char *key, int *exists)
{
	if (!ft_strncmp(key, "", 1))
		return ("$");
	if (!ft_strncmp(key, "$", 2))
		return ("Minishell: not a valid id");
	return (get_val_from_env(envp, key, exists));
}

/**
 * get_val_from_env
	- Helper function to retrieve the value associated with a given key from
		the env variables.
 * @envp: The env variables array.
 * @key: The key to search for in the env variables.
 * @exists: Pointer to an integer that will be set to 1 if the key exists,
	otherwise 0.
 *
 * This function iterates through the env variables array to find the key.
 * If the key is found and is followed by an '=',
	it returns the value associated with the key.
 * If the key is found but not followed by an '=', it returns an empty string.
 * If the key is not found, it returns an empty string.
 *
 * Return: The value associated with the key,
	or an empty string if the key is not found.
 */
char	*get_val_from_env(char **envp, char *key, int *exists)
{
	char	*ret;
	int		i;

	i = -1;
	while (envp && envp[++i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			if (envp[i][ft_strlen(key)] == '=')
			{
				ret = envp[i] + ft_strlen(key) + 1;
				if (exists)
					*exists = 1;
				return (ret);
			}
			if (!envp[i][ft_strlen(key)])
			{
				if (exists)
					*exists = 1;
				return ("");
			}
		}
	}
	return ("");
}
