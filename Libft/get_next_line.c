/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:25:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:51:54 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//------------- GET NEXT LINE V1 -------------
//----------- read fd -----------

char	*ft_strchr_gnl(char *str, int c)
{
	unsigned char	b;
	int				i;

	b = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if ((unsigned char)str[i] == b)
			return ((char *)&str[i]);
		i++;
	}
	if (b == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

static char	*ft_set_line(char *line_buf)
{
	char		*left_c;
	ssize_t		i;

	i = 0;
	while (line_buf[i] != '\n' && line_buf[i] != '\0')
		i++;
	if (line_buf[i] == 0 || line_buf[1] == 0)
		return (NULL);
	left_c = ft_substr_gnl(line_buf, i + 1, ft_strlen_gnl(line_buf) - i);
	if (*left_c == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	line_buf[i + 1] = 0;
	return (left_c);
}

static char	*ft_fill_line_buf(int fd, char *left_c, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free(left_c), NULL);
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (!left_c)
			left_c = ft_strdup_gnl("");
		tmp = left_c;
		left_c = ft_strjoin_gnl(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	return (left_c);
}

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		left_c = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = ft_fill_line_buf(fd, left_c, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (left_c = NULL, NULL);
	left_c = ft_set_line(line);
	return (line);
}
