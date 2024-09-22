/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:14:46 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:14:46 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hashtable	*ft_add_element(t_hashtable *ht, char *key, char *value)
{
	int		hash;

	hash = ft_monkey_hash(key, ht->length);
	while (ht->element_array[hash])
	{
		if (ft_strncmp(ht->element_array[hash]->key, key, ft_strlen(key)) == 0)
		{
			ht = ft_ch_value(ht, key, value, 0);
			return (ht);
		}
		hash = (hash + 1) % ht->length;
	}
	ht->element_array[hash] = ft_create_element(key, value);
	return (ht);
}
