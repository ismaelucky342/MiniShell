/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:17:34 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:17:36 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		((char *)s)[count] = 0;
		count ++;
	}
}

/*#include <unistd.h>
#include <string.h>

int main (void)
{
	char str[34];
	char str2[34];

	strcpy(str,"This is string.h library function");
	strcpy(str2,"This is string.h library function");

	bzero(str,4);
	ft_bzero(str2,4);

	write(1, str, 34);
	write(1, "\n", 1);
	write(1, str2, 34);
	write(1, "\n", 1);

	return(0);
}*/
