/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_hashtable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:42:04 by jahuang           #+#    #+#             */
/*   Updated: 2022/01/21 23:59:15 by jahuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
