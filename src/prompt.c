/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:59:36 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 19:00:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <bits/local_lim.h>
#include <limits.h>

extern int	g_exit;

char	*get_host_name(void)
{
	char	hostname[1024];
	char	*host;
	char	*dot;

	if (gethostname(hostname, 1024) == 0)
	{
		dot = strchr(hostname, '.');
		if (dot)
			host = ft_strndup(hostname, dot - hostname);
		else
			host = ft_strdup(hostname);
	}
	else
		host = ft_strdup("unknown");
	return (host);
}

char	*process_directory(char *original_dir, char *home)
{
	char	*dir;
	char	*temp;

	dir = original_dir;
	if (home && ft_strncmp(dir, home, ft_strlen(home)) == 0)
	{
		dir += ft_strlen(home);
		if (*dir == '/')
			dir++;
		temp = ft_strjoin("~/", dir);
		if (temp)
		{
			free(original_dir);
			original_dir = temp;
		}
	}
	return (original_dir);
}

char	*build_prompt(char *user, char *host, char *dir)
{
	char	*prompt;
	char	*temp;

	if (user && host)
	{
		prompt = ft_strjoin(user, "@");
		temp = ft_strjoin_free(prompt, host);
		prompt = ft_strjoin_free(temp, ":");
	}
	else
		prompt = ft_strdup("");
	prompt = ft_strjoin_free(prompt, dir);
	prompt = ft_strjoin_free(prompt, "\001\x1b[0m\002$ ");
	return (prompt);
}

char	*ft_prompt(char **env)
{
	char	*user;
	char	*host;
	char	*prompt;
	char	*home;
	char	*original_dir;

	user = get_value_from_env(env, "USER", NULL);
	home = get_value_from_env(env, "HOME", NULL);
	original_dir = getcwd(NULL, 0);
	if (!original_dir)
		original_dir = ft_strdup("");
	host = get_host_name();
	original_dir = process_directory(original_dir, home);
	prompt = build_prompt(user, host, original_dir);
	free(original_dir);
	free(host);
	return (prompt);
}
