/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:38:00 by apollo            #+#    #+#             */
/*   Updated: 2024/11/30 11:38:16 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/**
* @brief Checks if PWD is present in the environment and creates a backup if not.
*
* This function verifies if the PWD variable is present in the environment.
* If it is not present, it creates a backup of the current working directory
* using getcwd() and adds it to the environment.
*
* @param boogeyman Pointer to the `t_minishell` structure containing the
* state of the minishell.
* @return int Returns `OK` if the operation was successful, `KO` on error.
*/
int	ft_check_and_backup_pwd(t_minishell *boogeyman)
{
	char	*pwd;
	char	*backup_pwd;
	int		exists;

	get_value_from_env(boogeyman->envp, "PWD", &exists);
	if (!exists)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (KO);
		backup_pwd = ft_strjoin("PWD=", pwd);
		free(pwd);
		if (!backup_pwd)
			return (KO);
		if (ft_new_env(boogeyman, backup_pwd) == KO)
		{
			free(backup_pwd);
			return (KO);
		}
		free(backup_pwd);
		boogeyman->aux_pwd = ft_strdup(pwd);
	}
	return (OK);
}

/**
* @brief Removes the backup PWD from the environment if it exists.
*
* This function checks if the backup PWD variable is present in the environment
* and removes it if it exists.
*
* @param boogeyman Pointer to the `t_minishell` structure containing the
* state of the minishell.
*/
void	ft_remove_backup_pwd(t_minishell *boogeyman)
{
	char	**current;
	char	*key = "PWD";
	int		exists;

	get_value_from_env(boogeyman->envp, key, &exists);
	if (exists)
	{
		current = boogeyman->envp;
		while (*current)
		{
			if (!ft_strncmp(*current, key, ft_strlen(key)))
			{
				free(*current);
				while (*(current + 1))
				{
					*current = *(current + 1);
					current++;
				}
				*current = NULL;
				boogeyman->env_elems--;
				break ;
			}
			current++;
		}
	}
}
