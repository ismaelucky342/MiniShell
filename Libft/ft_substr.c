/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:52:20 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/12 12:52:22 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substr_funct(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*res;

	count = 0;
	while (s[start + count])
		count ++;
	if (count >= len)
		count = len;
	res = (char *)malloc(count +1);
	if (res == 0)
		return (0);
	res[count] = 0;
	if (len != 0)
		count --;
	while (count > 0)
	{
		res[count] = s[start + count];
		count --;
	}
	if (len != 0)
		res[count] = s[start + count];
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (slen <= start)
	{
		res = (char *)malloc(1);
		if (res == 0)
			return (0);
		res[0] = s[slen];
	}
	else
		res = ft_substr_funct(s, start, len);
	return (res);
}

/*#include <stdio.h>

int	main(void)
{
	char	test[20];

	strcpy(test, "Hola que tal");
	printf("%s\n", ft_substr(test, 400, 20));
	return (0);
}*/
