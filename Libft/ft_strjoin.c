/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ismherna <ismherna@student.42madrid>       +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/02/12 11:51:58 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (OK);
	ft_strlcpy(dst, s1, ft_strlen(s2) + ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (dst);
}

/*int 	main()
{
	const	char *string1 = "hola";
	const	char *string2 = " mundo";

	char	*resultado = ft_strjoin(string1, string2);
	if(resultado)
	{
		printf("la cadena unida es: %s", resultado);
		free(resultado);
	}else{
		printf("ERROR CADENA NULA");
	}
	return (OK);
}*/