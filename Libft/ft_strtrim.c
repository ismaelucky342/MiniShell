/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:05:40 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 16:05:40 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;

	if ((!*s1 && !*set) || (!*s1 && *set))
		return (ft_strdup(""));
	end = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[end - 1]))
		end--;
	while (ft_strchr(set, s1[start]))
		start++;
	return (ft_substr(s1, start, end - start));
}
/*int		main(void){

	const char *string = "	hola mundo  ";
	const char *trimeo = " \t\n";

	char	*cadena = ft_strtrim(*string, *trimeo);

	printf("La cadena original es: %s\n", string);
	printf("la cadena recortada es: %s\n", cadena);
	free(cadena);
	return (OK);
}*/
