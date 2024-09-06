/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:11:25 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 13:50:01 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static const char	*get_prompt_color(void)
{
	if (g_exit == 0)
		return (COLOR_BOLD_GREEN_TEXT);
	else
		return (COLOR_BOLD_RED_TEXT);
}

static void	print_prompt_content(const char *color, const char *path)
{
	ft_printf_fd(2, "%s➜  %s%s > %s", color, COLOR_BOLD_CYAN_TEXT, path,
		COLOR_RESET);
}

void	print_prompt(int sloc)
{
	char		prompt[LINE_MAX];
	int			i;
	int			last;
	const char	*color;

	last = 0;
	if (!g_exit && sloc)
		g_exit = sloc;
	color = get_prompt_color();
	if (!getcwd(prompt, LINE_MAX))
	{
		print_prompt_content(color, "minishell");
		return ;
	}
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '/')
			last = i + 1;
	}
	print_prompt_content(color, &prompt[last]);
}
