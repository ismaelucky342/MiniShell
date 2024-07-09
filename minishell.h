/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:19:12 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/06/04 12:19:14 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <stdlib.h>
# include <signal.h>
// external libraries
# include <readline/history.h>
# include <readline/readline.h>
# include <libft.h>

//INPUT STRUCT 
typedef struct input_struct
{
    __uint8_t  num_of_commands; 
    t_command  **commands;      
    t_list     **environment;   
    __int8_t   status_info;     
} input_t;


//FILE DESCRIPTOR
enum
{
	STDIN_FD = 0,
	STDOUT_FD = 1,
	STDERR_FD = 2
};

// ERRORS MANAGEMENT
typedef enum error_code
{
	ERR_VIEW = 1,
	ERR_NOT_IDENTIFIED = 2,
	ERR_MEMORY = 3,
	ERR_NOT_FOUND = 4,
	ERR_FORMAT = 5,
	ERR_EMPTY = 6
} error_t;

// ENV
typedef struct env_struct
{
	char	*name;
	char	*value;
}				t_env;


// CMD
typedef struct cmd_struct
{
    int         argument_count; // Número de argumentos
    char        **arguments;    // Array de punteros a argumentos
    int         file_descriptors[3]; // Descriptores de archivo para stdin, stdout, stderr
    __int8_t    status_info;    // Información de estado
} cmd_t;


#endif
