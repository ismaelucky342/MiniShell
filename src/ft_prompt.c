/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:29:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 15:19:56 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_is_exec;

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
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

char	*ft_prompt(char **env)
{
	char	*user;
	char	*host;
	char	*prompt;
	char	*home;
	char	*original_dir;

	user = get_val_from_env(env, "USER", NULL);
	home = get_val_from_env(env, "HOME", NULL);
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

void	update_prompt(t_mini *boogeyman)
{
	free(boogeyman->custom_prompt);
	boogeyman->custom_prompt = ft_prompt(boogeyman->envp);
	rl_clear_visible_line();
	rl_on_new_line();
	rl_replace_line(boogeyman->custom_prompt, 0);
	rl_redisplay();
}
