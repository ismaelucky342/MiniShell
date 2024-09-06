/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monkey_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:03:17 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:03:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_monkey_hash(char *str, int length)
{
	int		index;
	int		result;
	int		monkey_number;

	if (length <= 0)
	{
		ft_printf_fd(2, "Error: Hash table length must be positive.\n");
		return (-1);
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

/*
int	ft_monkey_hash(char *str, int length)
{
	int		index;
	int		result;
	int		monkey_number;

	if (length <= 0)
	{
		ft_printf_fd(2, "Error: Hash table length must be positive.\n");
		return (-1); // Return an invalid index or handle as needed
	}
	index = 0;
	result = 0;
	monkey_number = 89;
	// Compute the hash value
	while (str[index])
	{
		result += monkey_number * (int)str[index] * index;
		index++;
	}
	// Ensure the result is within the bounds of the hash table
	return ((result % length + length) % length); // Handle negative values
}
*/