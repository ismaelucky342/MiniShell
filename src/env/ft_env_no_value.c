/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_no_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:59:07 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/20 17:19:53 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_valid_env_entry(char *entry)
{
	return (ft_strchr(entry, '=') != NULL);
}

void	ft_env_no_value(t_minishell *sack)
{
	int	i;
	int	j;

	i = 0;
	while (sack->envp && sack->envp[i])
	{
		if (!ft_is_valid_env_entry(sack->envp[i]))
		{
			free(sack->envp[i]);
			j = i;
			while (sack->envp[j])
			{
				sack->envp[j] = sack->envp[j + 1];
				j++;
			}
			sack->env_elems--;
		}
		else
			i++;
	}
}
