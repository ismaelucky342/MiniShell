/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:25:02 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/31 14:25:07 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Checks whether or not the inputted string belongs to a builtin or not
 */
int	isbuiltin(char *str)
{
	size_t		len;

	len = ft_strlen(str);
	if ((len >= 2 && ft_strcmp(str[len - 2], "cd"))
		|| (len >= 4 && ft_strcmp(str[len - 4], "echo"))
		|| (len >= 3 && ft_strcmp(str[len - 3], "env"))
		|| (len >= 4 && ft_strcmp(str[len - 4], "exit"))
		|| (len >= 6 && ft_strcmp(str[len - 6], "export"))
		|| (len >= 3 && ft_strcmp(str[len - 3], "pwd"))
		|| (len >= 5 && ft_strcmp(str[len - 5], "unset")))
		return (KO);
	return (OK);
}
