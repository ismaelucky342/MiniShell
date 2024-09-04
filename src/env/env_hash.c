/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:48:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/02 16:09:58 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_env2hashtable(char **env, t_hashtable *hashtable, int array_len)
{
    int char_index;
    int hash_index;
    char *key;
    char *value;
    t_element *new_element;

    while (*env)
    {
        char_index = ft_index(*env, '=');
        if (char_index == -1)
        {
            env++;
            continue;
        }

        key = ft_substr(*env, 0, char_index);
        value = ft_substr(*env, char_index + 1, ft_strlen(*env) - char_index - 1);

        if (!key || !value)
        {
            perror("Malloc");
            free(key);
            free(value);
            env++;
            continue;
        }

        hash_index = ft_monkey_hash(key, array_len);

        t_element *current = hashtable->element_array[hash_index];
        while (current)
        {
            if (strcmp(current->key, key) == 0)
            {
                free(current->value);
                current->value = value;
                free(key);
                break;
            }
            current = current->next;
        }

        if (!current)
        {
            new_element = ft_create_element(key, value);
            if (!new_element)
            {
                perror("Malloc");
                free(key);
                free(value);
                env++;
                continue;
            }
            new_element->next = hashtable->element_array[hash_index];
            hashtable->element_array[hash_index] = new_element;
        }

        free(key);
        free(value);

        env++;
    }
}

t_hashtable *ft_create_envhash(char **env)
{
    t_hashtable *env_hashtable;
    int array_len;

    array_len = ft_arraylen(env);
    if (array_len == 0)
    {
        // Si no hay variables de entorno, se puede crear una tabla hash con un tamaño inicial predeterminado
        array_len = 4242;
    }
    else
    {
        // Calcula un tamaño de tabla hash adecuado
        array_len = ft_next_prime(array_len * 3);
    }

    env_hashtable = ft_create_hashtable(array_len);
    if (!env_hashtable)
    {
        perror("Malloc");
        return NULL;
    }

    ft_env2hashtable(env, env_hashtable, array_len);
    return env_hashtable;
}


