/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:20:39 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/16 15:20:42 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*minint(char *res)
{
	res = (char *)malloc(12);
	if (res == 0)
		return (0);
	ft_strlcpy(res, "-2147483648", 12);
	return (res);
}

static void	ft_passnb(int nb, char *res)
{
	if (nb < 0)
	{
		nb = -nb;
		ft_passnb(nb, res);
	}
	else if (nb > 9)
	{
		ft_passnb(nb / 10, res -1);
		ft_passnb(nb % 10, res);
	}
	else
		*res = nb + 48;
}

static int	ft_numsize(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i ++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		n2;
	int		len;
	int		sign;

	res = 0;
	sign = 0;
	if (n == -2147483648)
		return (minint(res));
	n2 = n;
	if (n < 0)
	{
		n2 = -n;
		sign = 1;
	}
	len = ft_numsize(n2);
	res = malloc(len +1 + sign);
	if (res == 0)
		return (0);
	ft_passnb(n, &res[len + sign -1]);
	if (sign == 1)
		res[0] = '-';
	res[len + sign] = 0;
	return (res);
}

/*#include <stdio.h>
int	main(void)
{
	char	*test = ft_itoa(1234);
	printf("%s\n", test);
	return (0);
}*/
