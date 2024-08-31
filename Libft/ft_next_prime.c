/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_prime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:22:36 by ismherna          #+#    #+#             */
/*   Updated: 2024/07/21 13:22:37 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_next_prime(int nbr)
{
	int	result;

	result = nbr;
	while (ft_is_prime(result) == 0)
		result++;
	return (result);
}
