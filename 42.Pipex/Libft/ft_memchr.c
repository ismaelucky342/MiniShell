/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:18:50 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:18:51 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count_str;
	unsigned char	*str;

	str = (unsigned char *)s;
	count_str = 0;
	while (count_str < n)
	{
		if (str[count_str] == (unsigned char)c)
			return ((void *)(s + count_str));
		count_str ++;
	}
	return (0);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	test[21];
	int		nb;

	nb = 15;
	strcpy(test, "aaaaaaaaaaaaaaaaaaa");
	printf("%s\n", (char *)memchr(test, 'b', nb));
	printf("%s\n", (char *)ft_memchr(test, 'b', nb));
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	//printf("%s", (char *)ft_memchr(tab, -1, 7));
	//return (0);
}*/
