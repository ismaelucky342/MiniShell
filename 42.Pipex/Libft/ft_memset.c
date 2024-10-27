/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:00 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:20:01 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	count;

	count = 0;
	while (count < len)
	{
		*(char *)b = (unsigned char)c;
		count ++;
		b ++;
	}
	b = b - count;
	return (b);
}

/*#include <stdio.h>
#include <string.h>

int main (void)
{
   char str[50];
   char str2[50];

   strcpy(str,"This is string.h library function");
   strcpy(str2,"This is string.h library function");
   puts(str);
   puts(str2);

   memset(str,'$',50);
   puts(str);
   ft_memset(str2,'&',50);
   puts(str2);
   
   return(0);
}*/
