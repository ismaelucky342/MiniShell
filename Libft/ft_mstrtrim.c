/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstrtrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:57:49 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 16:58:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mstrtrim(t_mem_context *ctx, char const *s1, char const *set)
{
	size_t	end;
	size_t	start;

	if ((!*s1 && !*set) || (!*s1 && *set))
		return (ft_strdup(  ""));
	end = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[end - 1]))
		end--;
	while (ft_strchr(set, s1[start]))
		start++;
	return (ft_substr(ctx, s1, start, end - start));
}