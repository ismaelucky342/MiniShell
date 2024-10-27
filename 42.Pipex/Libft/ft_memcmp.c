/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:19:04 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:19:07 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	count;
	size_t			comp;
	char			*str1;
	char			*str2;

	count = 0;
	comp = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	while (count < n)
	{
		comp = (unsigned char)str1[count] - (unsigned char)str2[count];
		if (comp != 0)
			return (comp);
		count ++;
	}
	return (comp);
}
