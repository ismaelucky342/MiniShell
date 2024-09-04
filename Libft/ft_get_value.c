/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:01:05 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:01:05 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_value(t_hashtable *hashtable, char *key)
{
	int			index;
	int			key_len;
	int			table_len;
	int			hash;
	t_element	**elem_holder;

	if (!key)
		return (NULL);
	index = 0;
	key_len = ft_strlen(key);
	table_len = hashtable->length;
	hash = ft_monkey_hash(key, hashtable->length);
	elem_holder = hashtable->element_array;
	while (elem_holder[index + hash] && \
		hash == ft_monkey_hash(elem_holder[index + hash]->key, table_len)
	)
	{
		if (ft_strncmp(elem_holder[index + hash]->key, key, key_len) == 0)
			return (elem_holder[index + hash]->value);
		index++;
	}
	return (NULL);
}
