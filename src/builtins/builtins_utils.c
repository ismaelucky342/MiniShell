/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:58:46 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 22:59:21 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isbuiltin(char *str)
{
	if (!ft_strncmp(str, "cd", 3))
		return (1);
	else if (!ft_strncmp(str, "echo", 5))
		return (1);
	else if (!ft_strncmp(str, "exit", 5))
		return (1);
	else if (!ft_strncmp(str, "pwd", 4))
		return (1);
	else if (!ft_strncmp(str, "unset", 6))
		return (1);
	else if (!ft_strncmp(str, "export", 7))
		return (1);
	return (0);
}
