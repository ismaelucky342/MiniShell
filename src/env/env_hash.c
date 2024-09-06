/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:48:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 13:56:00 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env2hashtable(char **env, t_hashtable *hashtable, int array_len)
{
	while (*env)
	{
		process_env_variable(env, hashtable, array_len);
		env++;
	}
}

void	process_env_variable(char **env, t_hashtable *hashtable, int array_len)
{
	int		char_index;
	char	*key;
	char	*value;

	char_index = ft_index(*env, '=');
	if (char_index == -1)
		return ;
	key = ft_substr(*env, 0, char_index);
	value = ft_substr(*env, char_index + 1, ft_strlen(*env) - char_index - 1);
	if (!key || !value)
	{
		perror("Malloc");
		free(key);
		free(value);
		return ;
	}
	insert_into_hashtable(key, value, hashtable, array_len);
}

void	insert_into_hashtable(char *key, char *value,
					t_hashtable *hashtable, int array_len)
{
	int			hash_index;
	t_element	*current;

	hash_index = ft_monkey_hash(key, array_len);
	current = hashtable->element_array[hash_index];
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			free(key);
			return ;
		}
		current = current->next;
	}
	add_new_element(key, value, hashtable, hash_index);
}

void	add_new_element(char *key, char *value, t_hashtable *hashtable,
		int hash_index)
{
	t_element	*new_element;

	new_element = ft_create_element(key, value);
	if (!new_element)
	{
		perror("Malloc");
		free(key);
		free(value);
		return ;
	}
	new_element->next = hashtable->element_array[hash_index];
	hashtable->element_array[hash_index] = new_element;
}

t_hashtable	*ft_create_envhash(char **env)
{
	t_hashtable	*env_hashtable;
	int			array_len;

	array_len = ft_arraylen(env);
	if (array_len == 0)
	{
		array_len = 4242;
	}
	else
	{
		array_len = ft_next_prime(array_len * 3);
	}
	env_hashtable = ft_create_hashtable(array_len);
	if (!env_hashtable)
	{
		perror("Malloc");
		return (NULL);
	}
	ft_env2hashtable(env, env_hashtable, array_len);
	return (env_hashtable);
}
