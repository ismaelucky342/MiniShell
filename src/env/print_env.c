/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:48:50 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 13:29:19 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_env(t_hashtable *env_hashtable, int is_export)
{
	int			index;
	t_element	*env_element;

	index = 0;
	if (!env_hashtable || !env_hashtable->element_array)
	{
		fprintf(stderr, "Error: Invalid hashtable or element array\n");
		return ;
	}
	while (index < env_hashtable->length)
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
		index++;
	}
}
