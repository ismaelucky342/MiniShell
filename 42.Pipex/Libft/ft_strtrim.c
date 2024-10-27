/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:07:40 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/12 17:07:42 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char c1, const char *set)
{
	int		index;

	index = 0;
	while (set[index])
	{
		if (c1 == set[index])
			return (0);
		index ++;
	}
	return (1);
}

static int	ft_find_len(const char *s1, const char *set)
{
	int		index;
	int		len;

	len = 0;
	index = 0;
	while (s1[index] && ft_search(s1[index], set) == 0)
		index ++;
	while (s1[index])
	{
		index ++;
		len ++;
	}
	index --;
	while (index > 0 && ft_search(s1[index], set) == 0)
	{
		len --;
		index --;
	}
	if (len < 0)
		len = 0;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		index;
	int		res_index;
	int		len;
	char	*res;

	if (!s1 || !set)
		return (0);
	len = ft_find_len(s1, set);
	res = (char *)malloc(len +1);
	if (res == 0)
		return (0);
	res[len] = 0;
	if (len == 0)
		return (res);
	index = 0;
	res_index = 0;
	while (s1[index] && ft_search(s1[index], set) == 0)
		index ++;
	while (s1[index] && res_index != len)
	{
		res[res_index] = s1[index];
		index ++;
		res_index ++;
	}
	return (res);
}

/*int	main(void)
{
	char	s1[] = "          ";

	printf("%s\n", ft_strtrim(s1, " "));
	return (0);
}*/
