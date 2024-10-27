/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:17:47 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:17:51 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;

	if (size > 0)
		if ((__SIZE_MAX__ / size) <= count)
			return (0);
	res = (char *)malloc(count * size);
	if (res == 0)
		return (0);
	ft_bzero(res, count * size);
	return (res);
}
