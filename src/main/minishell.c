/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/07/21 13:48:50 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int general_signal;







/*
Inicialización de Variables:

	señales 
	tokens arbol 
	type: identificar comando en el arbol 
	exec entonrno y etc  



Inicialización exec: 

	Crear un entorno 
	Inicializamos la estructura, como el estado de salida

Bucle Principal: 

	ft_restore_terminal(0): Restauramos la configuración inicial del terminal
	ft_configure_terminal: preparamos el terminal

	Parseo de Comandos: El parser convierte la entrada del usuario en un árbol de sintaxis. La salida del parser es el tipo de nodo (comando, redirección, etc.) y el árbol (token_tree).

	ft_restore_terminal(1): Restaura el terminal a su estado previo después del parseo.

	Verificación de Errores
	
	Ejecución de Comandos

	Limpieza




Flujo General:
	Inicialización del entorno de ejecución.
	Configuración del terminal para capturar comandos.
	Parseo de la entrada del usuario y construcción del árbol de sintaxis.
	Ejecución del comando basado en el árbol generado.
	Limpieza de los recursos utilizados.
*/

