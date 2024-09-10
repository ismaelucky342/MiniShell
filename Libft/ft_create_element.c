/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/04 13:02:31 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:02:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


t_element	*ft_create_element(char *key, char *value)
{
	t_element *new_element;

	new_element = (t_element *)malloc(sizeof(t_element));
	if (!new_element)
		return (NULL);

	new_element->key = ft_strdup(key);
	if (!new_element->key)
	{
		free(new_element); // Solo libera el objeto de `new_element`
		return (NULL);
	}

	new_element->value = ft_strdup(value);
	if (!new_element->value)
	{
		free(new_element->key); // Libera la memoria para `key`
		free(new_element);      // Libera la memoria para `new_element`
		return (NULL);
	}

	return (new_element);
}
