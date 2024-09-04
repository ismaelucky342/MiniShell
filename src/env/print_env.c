/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:48:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/02 15:46:25 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_print_env(t_hashtable *env_hashtable, int is_export)
{
    int index;
    t_element *env_element;

    if (!env_hashtable || !env_hashtable->element_array)
    {
        fprintf(stderr, "Error: Invalid hashtable or element array\n");
        return;
    }

    for (index = 0; index < env_hashtable->length; index++)
    {
        env_element = env_hashtable->element_array[index];

        while (env_element)
        {
            if (env_element->key && env_element->value)
            {
                if (is_export)
                    printf("export ");
                printf("%s=%s\n", env_element->key, env_element->value);
            }

            env_element = env_element->next;
        }
    }
}
