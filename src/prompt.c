/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:11:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 12:03:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef HOST_NAME_MAX
# define HOST_NAME_MAX 64
#endif

const char	*get_env_var(t_hashtable *env_hashtable, const char *var)
{
	return (ft_hashtable_get(env_hashtable, var));
}

static const char	*get_prompt_color(void)
{
	if (g_signals.exit_status == 0)
		return (COLOR_BOLD_GREEN_TEXT);
	else
		return (COLOR_BOLD_RED_TEXT);
}

static void	print_prompt_content(const char *color, const char *user,
		const char *host, const char *path)
{
	if (!user)
		user = "unknown_user";
	if (!host || host[0] == '\0')
		host = "unknown_host";
	printf("%s%s@%s:%s~/%s%s$%s ", color, user, host, 
		COLOR_BOLD_CYAN_TEXT, path, COLOR_BOLD_WHITE_TEXT, COLOR_RESET);
}



void	print_prompt(int sloc, t_hashtable *env_hashtable)
{
	char		prompt[LINE_MAX];
	char		host[HOST_NAME_MAX];
	const char	*user;
	const char	*color;

	int i, last;
	last = 0;
	if (g_signals.exit_status == 0 && sloc)
		g_signals.exit_status = sloc;
	color = get_prompt_color();
	user = get_env_var(env_hashtable, "USER");
	gethostname(host, HOST_NAME_MAX);
	if (!getcwd(prompt, LINE_MAX))
	{
		print_prompt_content(color, user, host, "minishell");
		fflush(stdout);
		return ;
	}
	i = -1;
	while (prompt[++i])
		if (prompt[i] == '/')
			last = i + 1;
	print_prompt_content(color, user, host, &prompt[last]);
	fflush(stdout);
}
