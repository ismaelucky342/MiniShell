/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:42:34 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:40:32 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_remove_env_variables
	- Cleans up the env variables array by removing entries
 *                that do not contain an '=' character.
 * @boogeyman: A pointer to the t_mini structure containing the env
 *             variables array (envp).
 *
 * This function iterates through the envp array and frees any entry that does
 * not contain an '=' character. After freeing an entry, it shifts the remaining
 * entries in the array to fill the gap.
 */
void	ft_remove_env_variables(t_mini *boogeyman)
{
	int		i;
	int		j;

	i = -1;
	while (boogeyman->envp && boogeyman->envp[++i])
	{
		if (!ft_strchr(boogeyman->envp[i], '='))
		{
			free(boogeyman->envp[i]);
			j = --i;
			while (boogeyman->envp[++j])
				boogeyman->envp[j] = boogeyman->envp[j + 1];
		}
	}
}
/**
 * ft_remove_env
	- Removes an env variable from the minishell env.
 * @boogeyman: A pointer to the t_mini structure containing the env.
 * @key: The key of the env variable to be removed.
 *
 * This function searches for the env variable specified by the key in the
 * minishell env. If found,
	it frees the memory allocated for that variable,
 * decreases the count of env elements,
	and shifts the remaining env
 * variables to fill the gap.
 *
 * Return: Always returns 0.
 */

int	ft_remove_env(t_mini *boogeyman, char *key)
{
	int		i;
	int		j;

	i = -1;
	while (boogeyman->envp && boogeyman->envp[++i])
	{
		j = 0;
		while (boogeyman->envp[i][j] && key[j]
			&& (boogeyman->envp[i][j] == key[j]))
			++j;
		if (!key[j] && (!boogeyman->envp[i][j] || boogeyman->envp[i][j] == '='))
		{
			free(boogeyman->envp[i]);
			boogeyman->env_elems--;
			break ;
		}
	}
	while (boogeyman->envp && boogeyman->envp[i])
	{
		boogeyman->envp[i] = boogeyman->envp[i + 1];
		++i;
	}
	return (0);
}
