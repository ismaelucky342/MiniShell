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


t_element	*ft_create_element(t_mem_context *ctx, char *key, char *value)
{
	t_element *new_element;

	new_element = (t_element *)mmalloc(ctx, sizeof(t_element));
	if (!new_element)
		return (NULL);

	new_element->key = ft_mstrdup(ctx, key);
	if (!new_element->key)
	{
		mfree(ctx, (void **)&new_element);
		return (NULL);
	}

	new_element->value = ft_mstrdup(ctx, value);
	if (!new_element->value)
	{
		mfree(ctx, (void **)&new_element->key);
		mfree(ctx, (void **)&new_element);
		return (NULL);
	}

	return (new_element);
}
