/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:48:37 by jahuang           #+#    #+#             */
/*   Updated: 2024/07/20 21:57:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_element	*ft_create_element(char *key, char *value)
{
	t_element	*new_element;

	new_element = malloc(sizeof(t_element) * 1);
	if (!new_element)
		return (NULL);
	new_element->key = ft_strdup(key);
	new_element->value = ft_strdup(value);
	return (new_element);
}
