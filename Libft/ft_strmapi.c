/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:26:54 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/22 10:26:55 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		index;
	char	*res;

	if (!s)
		return (0);
	index = ft_strlen(s);
	res = (char *)malloc(index +1);
	if (res == 0)
		return (0);
	res[index] = 0;
	index = 0;
	while (s[index] != 0)
	{
		res[index] = f(index, s[index]);
		index ++;
	}
	return (res);
}
