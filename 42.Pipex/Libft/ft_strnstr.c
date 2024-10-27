/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:21:49 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:21:51 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	count_str;
	size_t	count_find;

	if (len == 0 && !str)
		return (0);
	count_str = 0;
	if (*to_find == 0)
		return ((char *)str);
	while (str[count_str] != 0 && count_str < len)
	{
		count_find = 0;
		while (str[count_str + count_find] == to_find[count_find])
		{
			if (count_str + count_find >= len)
				return (0);
			count_find ++;
			if (to_find[count_find] == 0)
				return ((char *)&str[count_str]);
		}
		count_str ++;
	}
	return (0);
}

/*#include <stdio.h>

int	main(void)
{
	char	teststr[] = "ajajjjajaxdhholahola";

	printf("%s\n", ft_strnstr(teststr, NULL, 15));
	return (0);
}*/
