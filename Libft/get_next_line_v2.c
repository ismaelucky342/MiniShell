/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:25:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/03/12 11:53:54 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
------------- GET NEXT LINE V2 -------------
------------ read file in stdin ------------
*/
char	*ft_strchr_gnl(const char *str, int c)
{
	unsigned char	b;
	
	b = (unsigned char)c;
	while (*str)
	{
		if ((unsigned char)*str == b)
			return ((char *)str);
		str++;
	}
	if (b == '\0')
		return ((char *)str);
	return (NULL);
}

static char	*ft_set_line(char *line_buffer)
{
	char		*left_c;
	size_t		i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0')
	{
		free(line_buffer);
		return (NULL); // No hay nueva línea, retornar NULL
	}
	left_c = ft_substr_gnl(line_buffer, i + 1, ft_strlen_gnl(line_buffer) - i - 1);
	if (!left_c || left_c[0] == '\0')
	{
		free(left_c);
		left_c = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (left_c);
}

static char	*ft_fill_line_buffer(char *left_c, char *buffer)
{
	ssize_t		b_read;
	char		*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		if (b_read == 0)
			break;
		buffer[b_read] = '\0';
		if (!left_c)
			left_c = ft_strdup_gnl("");
		tmp = left_c;
		left_c = ft_strjoin_gnl(tmp, buffer);
		free(tmp);
		if (ft_strchr_gnl(buffer, '\n'))
			break;
	}
	return (left_c);
}

char	*get_next_line_v2(void)
{
	static char *left_c = NULL;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	
	line = ft_fill_line_buffer(left_c, buffer);
	free(buffer);
	
	if (!line)
	{
		left_c = NULL;
		return (NULL);
	}
	
	left_c = ft_set_line(line);
	return (line);
}
