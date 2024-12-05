/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:42:34 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:30:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/**
 * ft_remove_env_variables - Cleans up the environment variables array by removing entries
 *                that do not contain an '=' character.
 * @boogeyman: A pointer to the t_minishell structure containing the environment
 *             variables array (envp).
 *
 * This function iterates through the envp array and frees any entry that does
 * not contain an '=' character. After freeing an entry, it shifts the remaining
 * entries in the array to fill the gap.
 */
void	ft_remove_env_variables(t_minishell *boogeyman)
{
	int	i;
	int	j;

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
 * ft_remove_env - Removes an environment variable from the minishell environment.
 * @boogeyman: A pointer to the t_minishell structure containing the environment.
 * @key: The key of the environment variable to be removed.
 *
 * This function searches for the environment variable specified by the key in the
 * minishell environment. If found, it frees the memory allocated for that variable,
 * decreases the count of environment elements, and shifts the remaining environment
 * variables to fill the gap.
 *
 * Return: Always returns 0.
 */

int	ft_remove_env(t_minishell *boogeyman, char *key)
{
	int	i;
	int	j;

	i = -1;
	while (boogeyman->envp && boogeyman->envp[++i])
	{
		j = 0;
		while (boogeyman->envp[i][j] && key[j] && (boogeyman->envp[i][j] == key[j]))
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