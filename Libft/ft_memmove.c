/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:19:35 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:19:36 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*revmemcpy(void *dest, const void *src, size_t n)
{
	if (dest != 0 || src != 0)
	{
		while (n > 0)
		{
			*(char *)(dest + n -1) = *(char *)(src + n -1);
			n --;
		}
	}
	return (dest);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (dst == 0 && src == 0)
		return (0);
	if (dst < src)
		ft_memcpy(dst, src, n);
	else
		revmemcpy(dst, src, n);
	return (dst);
}

/*int main (void)
{
	int size = 128 * 1024 * 1024;
 	char *dst = (char *)malloc(sizeof(char) * size);
 	char *data = (char *)malloc(sizeof(char) * size);

 	__builtin___memset_chk (data, 'A', size, __builtin_object_size (data, 0));

	memmove(dst, data, size);

	char str[17];

	strcpy(str,"0123456789101112");
	puts(str);

	memmove(str +1,str,14);
	write(1, str, 25);
	write(1, "\n", 1);
	strcpy(str,"0123456789101112");
	ft_memmove(str +1,str,14);
	write(1, str, 25);
	write(1, "\n", 1);

	return(0);
}*/
