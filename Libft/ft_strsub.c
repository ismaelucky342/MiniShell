/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:04:48 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 15:58:48 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(t_mem_context *ctx, char const *s, unsigned int start,
		size_t len)
{
	size_t	length;
	char	*out;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	out = NULL;
	if ((start + len) <= length)
	{
		out = mmalloc(ctx, sizeof(char) * (len + 1));
		if (out)
		{
			ft_strncpy(out, s + start, len);
			out[len] = '\0';
		}
	}
	return (out);
}
