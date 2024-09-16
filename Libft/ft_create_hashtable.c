/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_hashtable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:44:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/16 13:44:18 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hashtable	*ft_create_hashtable(int length)
{
	int			index;
	t_hashtable	*new_hashtable;

	index = 0;
	new_hashtable = (t_hashtable *)malloc(sizeof(t_hashtable) * 1);
	if (!new_hashtable)
		return (NULL);
	new_hashtable->length = length;
	new_hashtable->element_array = malloc(sizeof(t_element) * length);
	if (!new_hashtable->element_array)
	{
		free(new_hashtable);
		return (NULL);
	}
	while (index < length)
	{
		new_hashtable->element_array[index] = NULL;
		index++;
	}
	return (new_hashtable);
}
