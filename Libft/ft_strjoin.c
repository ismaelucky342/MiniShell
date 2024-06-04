/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:37:12 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/12 15:37:15 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		count;
	char	*res;

	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(len1 + len2 +1);
	if (res == 0)
		return (0);
	count = 0;
	while (count < (len1 + len2))
	{
		if (count < len1)
			res[count] = s1[count];
		else
			res[count] = s2[count - len1];
		count ++;
	}
	res[count] = 0;
	return (res);
}

/*#include <stdio.h>

int	main(void)
{
	char	test1[30] = "Hello ";
	char	test2[30] = " World";

	printf("%s\n", ft_strjoin(test1, test2));
	return (0);
}*/
