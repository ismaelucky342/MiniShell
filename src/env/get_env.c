/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:11:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 11:11:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*ft_hashtable_get(t_hashtable *hashtable, const char *key)
{
	int			hash_index;
	t_element	*current;

	hash_index = ft_monkey_hash(key, hashtable->length);
	current = hashtable->element_array[hash_index];
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
