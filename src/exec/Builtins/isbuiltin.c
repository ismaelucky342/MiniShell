/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:40:24 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	isbuiltin(char *str)
{
	if (ft_strcmp(str, "cd") || ft_strcmp(str, "echo") || ft_strcmp(str, "env")
		|| ft_strcmp(str, "exit") || ft_strcmp(str, "export")
		|| ft_strcmp(str, "pwd") || ft_strcmp(str, "unset"))
		return (KO);
	return (OK);
}

