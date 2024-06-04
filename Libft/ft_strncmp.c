/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:21:31 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:21:32 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;
	size_t	comp;

	count = 0;
	comp = 0;
	while ((s1[count] != 0 || s2[count] != 0) && count < n)
	{
		comp = (unsigned char)s1[count] - (unsigned char)s2[count];
		if (comp != 0)
			return (comp);
		count ++;
	}
	return (0);
}

/*#include <stdio.h>

int	main(int n1, char **args)
{
	if (n1 != 4)
		return (1);
	int n3 = args[3][0] -48;
	printf("%d\n", n3);
	printf("%d\n", ft_strncmp(args[1], args[2], n3));
	return (0);
}*/
