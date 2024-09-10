/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:25:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 12:55:38 by ismherna         ###   ########.fr       */
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

	static t_signal_context signals;
	if (!signals.env_hashtable)
		init_signal_context(&signals);
	pos = 0;
	buf = (char *)malloc(4096);  // Usar malloc en lugar de malloc
	if (!buf)
		return (NULL);
	while (1)
	{
		ret = read(0, red, 1);
		if (ret == -1)
		{
			free(buf);  // Liberar buf si hay error de lectura
			return (NULL);
		}
		if (signals.reset_flag == 1)
		{
			signals.reset_flag = 0;
			pos = 0;  // Resetear el buffer
		}
		if (ret == 0 && pos == 0)  // Manejar Ctrl-D (EOF)
		{
			printf("  \b\b\nexit\n");
			
			free_env_hashtable(signals.env_hashtable);
			signals.env_hashtable = NULL;
			
			free(buf);  // Liberar la línea antes de salir
			
			exit(signals.exit_status);
		}
		if (ret == 0)
		{
			printf("  \b\b");  // Imprimir una nueva línea
		}
		else if (red[0] == '\n' || pos >= 4095)  // Fin de línea o buffer lleno
		{
			buf[pos] = '\0';
			return (buf);  // Devolver la línea leída
		}
		else
			buf[pos++] = red[0];  // Agregar el caracter al buffer
	}
}


