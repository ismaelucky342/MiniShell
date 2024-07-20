/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:25:49 by jahuang           #+#    #+#             */
/*   Updated: 2024/07/20 21:56:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hashtable	*ft_delete_element(t_hashtable *ht, char *key)
{
	int			hash_index;
	t_element	**elem_arr;

	hash_index = ft_monkey_hash(key, ht->length);
	elem_arr = ht->element_array;
	while (elem_arr[hash_index])
	{
		if (ft_strncmp(elem_arr[hash_index]->key, key, ft_strlen(key)) == 0)
		{
			ft_free_element(elem_arr[hash_index]);
			elem_arr[hash_index] = NULL;
			return (ht);
		}
		hash_index = (hash_index + 1) % ht->length;
	}
	return (ht);
}
