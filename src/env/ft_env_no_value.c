/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_no_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:59:07 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/30 11:09:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* @brief Checks if an environment variable entry is valid.
*
* Determines whether an entry (`entry`) contains an equal sign (`=`),
* indicating that the entry is a valid environment variable. Returns 1 if it is
* valid and 0
* otherwise.
*
* @param entry The environment variable entry to evaluate.
* @return int 1 if the entry is valid, 0 otherwise.
*/
static int	ft_is_valid_env_entry(char *entry)
{
	return (ft_strchr(entry, '=') != NULL);
}

/**
* @brief Removes environment variables without a value from the environment
* variables array.
*
* Iterates through the environment variables array (`boogeyman->envp`) and checks each
* entry to determine if it is valid using `ft_is_valid_env_entry`.
* If an invalid entry (without a value assigned) is found, its memory
* is freed and the remaining entries are shifted to fill the gap.
* The element count of the environment variables is decremented when
* an invalid entry is removed.
*
* @param boogeyman Pointer to the main structure containing the environment
* variables array and the element count.
*/
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
