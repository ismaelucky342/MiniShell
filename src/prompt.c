/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:59:36 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:41:56 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit;

char	*ft_prompt(char **env)
{
	char	*user;
	char	*host;
	char	*dir;
	char	*prompt;

	user = get_value_from_env(env, "USER", NULL);
	host = get_value_from_env(env, "HOSTNAME", NULL);
	dir = getcwd(NULL, 0);
	if (!dir)
		dir = ft_strdup("");
	if (user && host)
	{
		prompt = ft_strjoin(user, "@");
		prompt = ft_strjoin_free(prompt, host);
		prompt = ft_strjoin_free(prompt, ":");
	}
	else
		prompt = ft_strdup("");
	prompt = ft_strjoin_free(prompt, dir);
	prompt = ft_strjoin_free(prompt, "\001\x1b[0m\002 $> ");
	free(dir);
	return (prompt);
}
