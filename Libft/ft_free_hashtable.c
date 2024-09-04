/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_hashtable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:01:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:01:15 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Functions to free the hash table.
*/

void	ft_free_element(t_element *element)
{
	if (element)
	{
		if (element->key)
			free(element->key);
		if (element->value)
			free(element->value);
		free(element);
	}
	return ;
}

void	ft_free_hashtable(t_hashtable *hashtable)
{
	int	index;

	index = 0;
	if (hashtable->element_array)
	{
		while (index < hashtable->length)
		{
			if (hashtable->element_array[index])
				ft_free_element(hashtable->element_array[index]);
			index++;
		}
		free(hashtable->element_array);
	}
	if (hashtable)
		free(hashtable);
}
