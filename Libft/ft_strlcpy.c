/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:58 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:20:59 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size != 0)
	{
		while (count < size -1 && src[count] != 0)
		{
			dest[count] = src[count];
			count ++;
		}
		dest[count] = 0;
	}
	count = 0;
	while (src[count] != 0)
		count ++;
	return (count);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	src[24] = 	"Pasas que cosannnnnnnnn";
	char	aqui[] = 	"tengo 14 char";
	char	src2[24] = 	"Pasas que cosannnnnnnnn";
	char	aqui2[] = 	"tengo 14 char";

	printf("%d\n", ft_strlcpy(aqui, src, 14));
	printf("%s\n", aqui);
	printf("%lu\n", strlcpy(aqui2, src2, 14));
	printf("%s\n", aqui2);
	return (0);
}*/
