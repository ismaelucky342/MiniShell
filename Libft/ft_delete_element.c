/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:23:31 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:23:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_delete_element(t_hashtable *ht, char *key)
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
			return (KO);
		}
		hash_index = (hash_index + 1) % ht->length;
	}
	return (OK);
}
