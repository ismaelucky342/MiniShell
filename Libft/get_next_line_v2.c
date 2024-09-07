/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:25:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 17:32:14 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "libft.h"

char	*get_next_line_v2(void)
{
	char	*buf;
	int		ret;
	int		pos;
	char	red[2];

	static t_mem_context ctx; 
	static t_signal_context signals;
	if (!ctx.allocated_list)
		ft_bzero(&ctx, sizeof(t_mem_context));
	if (!signals.env_hashtable)
		init_signal_context(&signals);
	pos = 0;
	buf = (char *)mmalloc(&ctx, 4096);
	while (1)
	{
		ret = read(0, red, 1);
		if (ret == -1)
			return (NULL);
		if (signals.reset_flag == 1)
		{
			signals.reset_flag = 0;
			pos = 0;
		}
		if (ret == 0 && pos == 0)
		{
			printf("  \b\bexit\n");
			free_all_malloc(&ctx);
			exit(signals.exit_status);
		}
		if (!ret)
		{
			printf("  \b\b");
		}
		else if (red[0] == '\n' || pos >= 4095)
		{
			buf[pos] = '\0';
			return (buf);
		}
		else
			buf[pos++] = red[0];
	}
}
