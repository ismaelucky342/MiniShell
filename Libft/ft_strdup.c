/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:27 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:20:29 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*res;

	len = 0;
	while (s1[len] != 0)
		len ++;
	res = (char *)malloc(len +1);
	if (res == 0)
		return (0);
	while (len >= 0)
	{
		res[len] = s1[len];
		len --;
	}
	return (res);
}

/*#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	test[8];
	char	*test2;
	char	*test3;
	int		count;

	strcpy(test, "ef");
	test2 = strdup(test);
	test3 = ft_strdup(test);
	count = 0;
	while (test[count])
		count ++;
	write (1, &(char){count +48}, 1);
	write (1, "\n", 1);
	write (1, test, 6);
	write (1, "\n\n", 2);
	count = 0;
	while (test2[count])
		count ++;
	write (1, &(char){count +48}, 1);
	write (1, "\n", 1);
	write (1, test2, 6);
	write (1, "\n\n", 2);
	count = 0;
	while (test3[count])
		count ++;
	write (1, &(char){count +48}, 1);
	write (1, "\n", 1);
	write (1, test3, 6);
	return (0);
}*/
