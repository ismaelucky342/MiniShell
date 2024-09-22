/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:40:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/20 17:19:53 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_value(char *env_entry, char *key, int *exists)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (!ft_strncmp(env_entry, key, key_len) && env_entry[key_len] == '=')
	{
		if (exists)
			*exists = 1;
		return (env_entry + key_len + 1);
	}
	return (NULL);
}

char	*get_value_from_env(char **envp, char *key, int *exists)
{
	char	*value;
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		value = extract_value(envp[i], key, exists);
		if (value)
			return (value);
		i++;
	}
	if (exists)
		*exists = 0;
	return ("");
}
