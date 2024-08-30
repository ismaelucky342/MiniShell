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

#include "minishell.h"
#include "execution.h"

// Declaración de una variable global para manejar señales
int	g_signal;
t_exec	*fill_struct(void); //es un prototipo me gustan

int	main(void)
{
	void		*token_tree;  // Apuntador al árbol (AST)
	t_node_type	type;         // Tipo de nodo en el árbol de sintaxis
	t_exec		*exec;        // Estructura que guarda el estado de ejecución

	g_signal = 0;             // Inicializa la variable global g_signal

	// Inicializa la estructura de ejecución, incluyendo la tabla hash del entorno
	exec = fill_struct();
	if (!exec)                // Verifica que se haya inicializado correctamente
		return (-1);          // Si no, retorna -1 para indicar error
	
	while (1)                 // Bucle infinito para mantener el shell
	{
		token_tree = NULL;           // Inicializa el árbol de tokens a NULL
		ft_restore_terminal(0);      // Restaura la configuración del terminal
		ft_configure_terminal();      // Configura el terminal para la entrada del usuario
		
		// Parsear la entrada del usuario y construir el árbol de sintaxis (AST)
		type = parser(&token_tree, exec);
		
		ft_restore_terminal(1);      // Restaura la configuración original del terminal
		exec->type = type;           // Almacena el tipo de nodo en exec
		exec->tree = token_tree;     // Almacena el árbol de tokens en exec
		
		// Si no es un terminal interactivo y hay un error de parseo, sale del shell
		if (!isatty(STDIN_FILENO) && type == ERROR)//esa funcion verifica el fd hay que crearla o si se puede usarla de la stdlib
			exit_shell(exec, NULL, exec->exit_status); //falta crearlo 
		
		// Ejecuta el comando correspondiente en base al árbol de sintaxis
		execution(token_tree, type, exec); //falata crearlo 
		
		// Libera la memoria del árbol de tokens (AST)
		node_tree_delete(token_tree, type); // falta crearla
		
		// Resetea el árbol de tokens en exec para la siguiente iteración
		exec->tree = NULL;
	}
	return (0); // El programa retorna 0 indicando que terminó exitosamente (aunque en este caso es un bucle infinito)
}

// Función que inicializa y llena la estructura t_exec.
t_exec	*fill_struct(void)
{
	t_exec		*exec;  // Estructura que guarda el estado de ejecución
	extern char **environ; // Acceso a la lista de entorno del sistema

	// Reserva memoria para la estructura t_exec
	exec = malloc(sizeof(t_exec));
	if (!exec)
	{
		perror("Malloc"); // Manejo de error si falla la reserva de memoria
		return (NULL);
	}

	// Crea una tabla hash a partir del entorno del sistema
	exec->env_hashtable = ft_create_envhash(environ);
	if (!exec->env_hashtable) 
	{
		free(exec);
		perror("Error initializing env hashtable"); 
		return (NULL);
	}
	
	// Inicializa otros campos de la estructura t_exec
	exec->exit_status = EXIT_SUCCESS; // Inicializa el estado de salida a éxito
	exec->sub_process = 0;            // Inicializa la cantidad de subprocesos
	exec->tree = NULL;                // Inicializa el árbol de sintaxis a NULL
	exec->type = 0;                   // Inicializa el tipo de nodo a 0
	return (exec); // Retorna la estructura t_exec inicializada
}

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
