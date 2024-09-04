/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ch_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:02:43 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_element	*ft_get_element(t_hashtable *ht, char *key)
{
	int			index;
	int			elem_index;
	int			key_len;
	int			hash_nbr;

	index = 0;
	key_len = ft_strlen(key);
	hash_nbr = ft_monkey_hash(key, ht->length);
	while (index < ht->length)
	{
		elem_index = (index + hash_nbr) % ht->length;
		if (ht->element_array[elem_index] && \
			ft_strncmp(ht->element_array[elem_index]->key, key, key_len) == 0)
			return (ht->element_array[elem_index]);
		index++;
	}
	return (NULL);
}

t_hashtable	*ft_ch_value(t_hashtable *ht, char *key, char *value, int is_apnd)
{
	t_element	*element;
	char		*value_holder;

	element = ft_get_element(ht, key);
	if (!element)
		return (ht);
	value_holder = element->value;
	if (is_apnd)
		element->value = ft_strjoin(element->value, value);
	else
		element->value = ft_strdup(value);
	free(value_holder);
	return (ht);
}
