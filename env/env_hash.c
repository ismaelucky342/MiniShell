/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 00:16:12 by jahuang           #+#    #+#             */
/*   Updated: 2024/07/21 13:48:50 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env2hashtable(char **env, t_hashtable *hashtable, int array_len)
{
	int			char_index;
	int			hash_index;
	char		*key;
	char		*value;

	while (*env)
	{
		char_index = ft_index(*env, '=');
		key = ft_substr(*env, 0, char_index);
		value = ft_substr(
				*env,
				char_index + 1,
				ft_strlen(*env) - char_index - 1);
		hash_index = ft_monkey_hash(key, array_len);
		while (hashtable->element_array[hash_index])
		{
			hash_index = (hash_index + 1) % array_len;
		}
		hashtable->element_array[hash_index] = ft_create_element(key, value);
		free(key);
		free(value);
		env++;
	}
}

t_hashtable	*ft_create_envhash(char **env)
{
	t_hashtable	*env_hashtable;
	int			array_len;

	array_len = ft_arraylen(env);
	if (array_len == 0)
	{
		env_hashtable = ft_create_hashtable(4242);
		return (env_hashtable);
	}
	array_len = ft_next_prime(array_len * 3);
	env_hashtable = ft_create_hashtable(array_len);
	ft_env2hashtable(env, env_hashtable, array_len);
	return (env_hashtable);
}
