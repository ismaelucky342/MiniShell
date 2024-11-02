/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:42:45 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/02 22:35:18 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Aumenta el tamaño del entorno de la minishell al reservar más memoria.
 *
 * Esta función realoca el espacio para el array de punteros de cadenas que
 * representa las variables de entorno (`envp`) de la minishell. Si el tamaño
 * actual más 32 excede el límite de un entero, se devuelve un error.
 * Si la realocación es exitosa, los valores existentes son copiados a la
 * nueva memoria y se libera la memoria antigua.
 *
 * @param boogeyman Puntero a la estructura `t_minishell` que contiene el
 *                   estado de la minishell, incluyendo el entorno y su tamaño.
 * @return int Retorna `OK` si la realocación fue exitosa, `KO` en caso de
 *             error.
 */
static int	ft_env_realloc(t_minishell *boogeyman)
{
	char	**new_envp;
	char	**src;

	if (boogeyman->env_size + 32 < INT_MAX)
		boogeyman->env_size += 32;
	else
		return (KO);
	new_envp = ft_calloc(boogeyman->env_size, sizeof(char *));
	if (!new_envp)
		return (KO);
	src = boogeyman->envp;
	while (*src)
	{
		*new_envp++ = *src++;
	}
	free(boogeyman->envp);
	boogeyman->envp = new_envp - (src - boogeyman->envp);
	return (OK);
}

/**
 * @brief Añade una nueva entrada al entorno de la minishell.
 *
 * Esta función duplica la cadena `key_val` y la almacena en el array de
 * punteros `envp` en la posición correspondiente al número actual de elementos
 * (`env_elems`). Incrementa el contador de elementos del entorno.
 *
 * @param boogeyman Puntero a la estructura `t_minishell` que contiene el
 *                   estado de la minishell.
 * @param key_val Cadena que representa la nueva variable de entorno a añadir.
 */
static void	ft_entry(t_minishell *boogeyman, char *key_val)
{
	boogeyman->envp[boogeyman->env_elems] = ft_strdup(key_val);
	boogeyman->env_elems++;
}

/**
 * @brief Reemplaza una entrada existente en el entorno de la minishell.
 *
 * Busca la entrada correspondiente en el array `envp` y, si se encuentra,
 * libera la memoria de la entrada antigua y la reemplaza con una nueva
 * que corresponde a `key_val`.
 *
 * @param envp Array de punteros de cadenas que representa las variables de
 *             entorno.
 * @param key_val Nueva cadena que se utilizará para reemplazar la entrada.
 * @param key Cadena que se utiliza para buscar la entrada existente en `envp`.
 */
static void	ft_replace_entry(char **envp, char *key_val, char *key)
{
	char	**current;

	current = envp;
	while (*current)
	{
		if (!ft_strncmp(*current, key, ft_strlen(key)))
		{
			free(*current);
			*current = ft_strdup(key_val);
			break ;
		}
		current++;
	}
}

/**
 * @brief Añade una nueva variable de entorno a la minishell.
 *
 * Esta función verifica si hay espacio en el entorno para una nueva entrada.
 * Si no hay suficiente espacio, llama a `ft_env_realloc` para aumentar el
 * tamaño. Luego, se llama a `ft_entry` para agregar la nueva variable al
 * entorno.
 *
 * @param boogeyman Puntero a la estructura `t_minishell` que contiene el
 *                   estado de la minishell.
 * @param key_val Cadena que representa la nueva variable de entorno a añadir.
 * @return int Retorna `OK` si la operación fue exitosa, `KO` en caso de error.
 */
static int	ft_new_env(t_minishell *boogeyman, char *key_val)
{
	if (boogeyman->env_elems + 1 >= boogeyman->env_size)
	{
		if (ft_env_realloc(boogeyman))
		{
			ft_putendl_fd("Minishell: couldn't add more envp tuples",
				STDERR_FILENO);
			ft_memory_error(boogeyman);
			return (KO);
		}
	}
	ft_entry(boogeyman, key_val);
	return (OK);
}

/**
 * @brief Construye o actualiza una variable de entorno en la minishell.
 *
 * Esta función verifica si `key_val` contiene un signo igual para determinar
 * si se debe crear o actualizar una variable de entorno. Si la variable ya
 * existe y se debe actualizar, se llama a `ft_replace_entry`. Si no existe,
 * se llama a `ft_new_env` para crear una nueva entrada.
 *
 * @param boogeyman Puntero a la estructura `t_minishell` que contiene el
 *                   estado de la minishell.
 * @param key_val Cadena que representa la nueva variable de entorno a construir
 *                o actualizar.
 * @return int Siempre retorna `OK`.
 */
int	ft_env_build(t_minishell *boogeyman, char *key_val)
{
	char	*key;
	int		exists;

	if (ft_strchr(key_val, '='))
		key = ft_substr(key_val, 0, ft_strchr(key_val, '=') - key_val);
	else
		key = ft_strdup(key_val);
	get_value_from_env(boogeyman->envp, key, &exists);
	if (exists && ft_strchr(key_val, '='))
		ft_replace_entry(boogeyman->envp, key_val, key);
	else if (!exists)
		ft_new_env(boogeyman, key_val);
	free(key);
	return (OK);
}
