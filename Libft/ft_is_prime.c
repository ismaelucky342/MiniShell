/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:54 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:02:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_prime(int nbr)
{
	int	mod;

	mod = 2;
	while (mod < nbr / 2)
	{
		if (nbr % mod == 0)
			return (OK);
		mod++;
	}
	return (KO);
}
