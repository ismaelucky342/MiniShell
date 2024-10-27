/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:19:22 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:19:24 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	if (dest != 0 || src != 0)
	{
		count = 0;
		while (count < n)
		{
			*(char *)(dest + count) = *(char *)(src + count);
			count ++;
		}
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[34];
	char str2[34];

	strcpy(str,"Hola");
	strcpy(str2,"Hola");
	puts(str);
	puts(str2);

	memcpy(str +2,str,6);
	puts(str);
	ft_memcpy(str2 +2,str2,5);
	puts(str2);

	return(0);
}*/
