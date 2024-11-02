/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_no_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:59:07 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/02 22:38:42 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Verifica si una entrada de variable de entorno es válida.
 *
 * Determina si una entrada (`entry`) contiene un signo igual (`=`), 
 * lo que indica 
 * que la entrada es una variable de entorno válida. Retorna 1 si es 
 * válida y 0 
 * si no lo es.
 *
 * @param entry Entrada de variable de entorno que se va a evaluar.
 * @return int 1 si la entrada es válida, 0 en caso contrario.
 */
static int	ft_is_valid_env_entry(char *entry)
{
	return (ft_strchr(entry, '=') != NULL);
}

/**
 * @brief Elimina las variables de entorno sin valor del array de variables 
 * de entorno.
 *
 * Recorre el array de variables de entorno (`boogeyman->envp`) y verifica cada 
 * entrada para determinar si es válida utilizando `ft_is_valid_env_entry`. 
 * Si se encuentra una entrada no válida (sin un valor asignado), se libera 
 * su memoria y se desplazan las entradas restantes para llenar el vacío. 
 * Se decrementa el conteo de elementos de las variables de entorno al eliminar 
 * una entrada no válida.
 *
 * @param boogeyman Puntero a la estructura principal que contiene el array de 
 *                  variables de entorno y el conteo de elementos.
 */
void	ft_env_no_value(t_minishell *boogeyman)
{
	int	i;
	int	j;

	i = 0;
	while (boogeyman->envp && boogeyman->envp[i])
	{
		if (!ft_is_valid_env_entry(boogeyman->envp[i]))
		{
			free(boogeyman->envp[i]);
			j = i;
			while (boogeyman->envp[j])
			{
				boogeyman->envp[j] = boogeyman->envp[j + 1];
				j++;
			}
			boogeyman->env_elems--;
		}
		else
			i++;
	}
}
