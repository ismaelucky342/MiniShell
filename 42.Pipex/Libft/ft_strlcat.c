/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:40 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:20:42 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_dest;
	size_t	size_src;
	size_t	count;

	if (!size && !dest)
		return (0);
	size_dest = ft_strlen(dest);
	size_src = ft_strlen(src);
	if (size <= size_dest)
		return (size + size_src);
	else
		size_src += size_dest;
	count = 0;
	while (src[count] != 0 && size_dest < size -1)
	{
		dest[size_dest] = src[count];
		size_dest ++;
		count ++;
	}
	dest[size_dest] = 0;
	return (size_src);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	test1[10] = "hola ";
	char	test2[10] = "hola ";

	printf("%u\n", ft_strlcat(test1, "hola", 6));
	printf("%s\n", test1);
	printf("%lu\n", strlcat(test2, "hola", 6));
	printf("%s\n", test2);
	return (0);
}*/
