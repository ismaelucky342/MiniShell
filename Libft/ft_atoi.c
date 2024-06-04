/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:17:20 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:17:22 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_checkspaces(const char *str, int *count)
{
	while (str[*count] == ' ' || str[*count] == '\t' || str[*count] == '\n'
		|| str[*count] == '\r' || str[*count] == '\v' || str[*count] == '\f')
		*count = *count +1;
}

static void	ft_check1sign(const char *str, int *sign, int *count)
{
	if (str[*count] == '-')
	{
		*sign = 1;
		*count = *count +1;
	}
	else if (str[*count] == '+')
	{
		*sign = 0;
		*count = *count +1;
	}
}

int	ft_atoi(const char *str)
{
	int		count;
	int		sign;
	int		res;

	count = 0;
	res = 0;
	sign = 0;
	ft_checkspaces(str, &count);
	ft_check1sign(str, &sign, &count);
	while (str[count] >= '0' && str[count] <= '9')
	{
		if (sign == 1)
			res -= str[count] - '0';
		else
			res += str[count] - '0';
		if (str[count +1] >= '0' && str[count +1] <= '9')
			res = res * 10;
		count ++;
	}
	return (res);
}
