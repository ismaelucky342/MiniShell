/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:51:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 14:51:43 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	handle_sign(int *dir, long long *nbr, va_list ap)
{
	char	sign;

	sign = 0;
	if (dir[PF_SPEC] == 3 || dir[PF_SPEC] == 4)
	{
		*nbr = get_nbr(dir, ap);
		if (dir[PF_SPACE] == 1)
			sign = ' ';
		if (dir[PF_PLUS] == 1)
			sign = '+';
		if (*nbr < 0)
			sign = '-';
		if (sign != 0)
			dir[PF_WIDTH]--;
	}
	return (sign);
}

void	handle_conversion(char *n, long long nbr, int *dir, va_list ap)
{
	if (dir[PF_SPEC] == 3 || dir[PF_SPEC] == 4)
	{
		if (nbr >= 0)
			ft_itoa_b(n, (unsigned long long)nbr, dir);
		else
			ft_itoa_b(n, (unsigned long long)-nbr, dir);
	}
	else
		ft_itoa_b(n, (unsigned long long)get_nbr(dir, ap), dir);
}

void	handle_precision_and_width(char *n, int *dir)
{
	if (dir[PF_PREC] != -1)
		dir[PF_ZERO] = -1;
	if (dir[PF_PREC] < ft_strnlen(n, -1))
		dir[PF_PREC] = ft_strnlen(n, -1);
	dir[PF_WIDTH] -= dir[PF_PREC];
	if (n[0] == '\0' || n[0] == '0')
		dir[PF_S] = -1;
	if (dir[PF_SPEC] == 2 || dir[PF_S] == 1)
		dir[PF_WIDTH] -= 2;
}

int	to_nbr(char *buf, int *dir, va_list ap)
{
	long long	nbr;
	char		sign;
	char		n[70];

	sign = handle_sign(dir, &nbr, ap);
	handle_conversion(n, nbr, dir, ap);
	handle_precision_and_width(n, dir);
	return (ft_number_str(n, buf, sign, dir) - buf);
}
