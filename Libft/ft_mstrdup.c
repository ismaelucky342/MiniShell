/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:38:22 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 16:39:26 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mstrdup(t_mem_context *ctx, char *s1)
{
	size_t	len;
	char	*duplicate;

	len = ft_strlen(s1) + 1;
	duplicate = (char *)mmalloc(ctx, len);
	if (duplicate == NULL)
		return (NULL);
	ft_memcpy(duplicate, s1, len);
	return (duplicate);
}