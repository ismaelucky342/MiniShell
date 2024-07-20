/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monkey_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:48:19 by jahuang           #+#    #+#             */
/*   Updated: 2024/07/20 21:57:12 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_monkey_hash(char *str, int length)
{
	int	index;
	int	result;
	int	monkey_number;

	index = 0;
	result = 0;
	monkey_number = 89;
	while (str[index])
	{
		result += monkey_number * (int)str[index] * index;
		index++;
	}
	return (result % length);
}
