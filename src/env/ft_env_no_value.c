/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_no_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:59:07 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static int	ft_is_valid_env_entry(char *entry)
{
	return (ft_strchr(entry, '=') != NULL);
}

void	ft_env_no_value(t_minishell *boogeyman)
{
	int	i;
	int	j;

	i = 0;
	while (boogeyman->envp && boogeyman->envp[i])
	{
		if (!ft_is_valid_env_entry(boogeyman->envp[i]))
		{
			free(boogeyman->envp[i]);
			j = i;
			while (boogeyman->envp[j])
			{
				boogeyman->envp[j] = boogeyman->envp[j + 1];
				j++;
			}
			boogeyman->env_elems--;
		}
		else
			i++;
	}
}
