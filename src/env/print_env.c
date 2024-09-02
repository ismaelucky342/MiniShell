/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:48:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/07/21 13:48:50 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_print_env(t_hashtable *env_hashtable, int is_export)
{
    int index;
    t_element *env_element;

    if (!env_hashtable)
        return;

    for (index = 0; index < env_hashtable->size; index++)
    {
        env_element = env_hashtable->element_array[index];
        while (env_element)
        {
            if (is_export)
                printf("export ");
            printf("%s=", env_element->key);
            if (is_export)
                printf("\"%s\"", env_element->value);
            else
                printf("%s", env_element->value);
            printf("\n");
            env_element = env_element->next; // Manejo de colisiones
        }
    }
}
