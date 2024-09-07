/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msubstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:58:34 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 16:58:39 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_msubstr(t_mem_context *ctx, char const *s, unsigned int start, size_t len)
{
	char *str;
	size_t s_len;
	size_t max_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_mstrdup(ctx, ""));
	max_len = s_len - start;
	if (len > max_len)
		len = max_len;
	str = (char *)mmalloc(ctx, sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}