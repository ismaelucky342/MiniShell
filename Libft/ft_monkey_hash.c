/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monkey_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:05:22 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 11:05:22 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_monkey_hash(const char *str, int length)
{
	int		index;
	int		result;
	int		monkey_number;

	if (length <= 0)
	{
		ft_print_error("Error: ", -1, "Hash table length must be positive.");
	}
	index = 0;
	result = 0;
	monkey_number = 89;
	while (str[index])
	{
		result += monkey_number * (int)str[index] * index;
		index++;
	}
	return ((result % length + length) % length);
}
