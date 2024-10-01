/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:40:24 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/01 17:40:25 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	isbuiltin(char *str)
{
	if (ft_strcmp(str, "cd") || ft_strcmp(str, "echo") || ft_strcmp(str, "env")
		|| ft_strcmp(str, "exit") || ft_strcmp(str, "export")
		|| ft_strcmp(str, "pwd") || ft_strcmp(str, "unset"))
		return (OK);
	return (KO);
}

