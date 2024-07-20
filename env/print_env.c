/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:30:42 by jahuang           #+#    #+#             */
/*   Updated: 2022/01/27 12:41:39 by jahuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_hashtable *env_hashtable, int is_export)
{
	int			index;
	t_element	*env_element;

	index = 0;
	if (!env_hashtable)
		return ;
	while (index < env_hashtable->length)
	{
		if (env_hashtable->element_array[index])
		{
			env_element = env_hashtable->element_array[index];
			if (is_export)
				printf("export ");
			printf("%s=", env_element->key);
			if (is_export)
				printf("\"%s\"", env_element->value);
			else
				printf("%s", env_element->value);
			printf("\n");
		}
		index++;
	}
}
