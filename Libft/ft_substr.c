/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:22:53 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:22:53 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		s_len;
	size_t		max_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	max_len = s_len - start;
	if (len > max_len)
		len = max_len;
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}

/*int		main(void){

	const	char *stringI = "hola muundo";
	unsigned int   startI = 5;
	size_t		lenI = 6;

	char	*subcadena = ft_substr(stringI, startI, lenI);

	if(subcadena){
		printf("\n%s\n", subcadena);
		free(subcadena);
		}else {
			printf("ERROR CADENA NO VALIDA");

	}
	return (OK);
}*/