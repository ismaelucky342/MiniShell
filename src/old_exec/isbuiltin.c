/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:25:02 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/11/12 12:22:00 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks whether or not the inputted string belongs to a builtin or not
 * 
 * @param str
 * String containing the command to check for builtin. 
 */
int	isbuiltin(char *str)
{
	if (ft_strcmp(str, "cd") || ft_strcmp(str, "echo")
		|| ft_strcmp(str, "env") || ft_strcmp(str, "exit")
		|| ft_strcmp(str, "export") || ft_strcmp(str, "pwd")
		|| ft_strcmp(str, "unset"))
		return (KO);
	return (OK);
}
