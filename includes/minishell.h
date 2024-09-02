/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apollo <apollo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:07:41 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/09/02 12:32:00 by apollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include "AST.h"
# include "tokens.h"´
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>

# define HASH_TABLE_SIZE 100 // Define el tamaño de la tabla hash
# define BUILTINS 7
int					g_reset;
unsigned int		g_exit;

/*-----------------------------------------LIST STRUCT----------------------------------------------------*/

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

/*-----------------------------------------RETURN SIGNAL--------------------------------------------------*/
typedef enum return_signal
{
	CONTINUE,
	NOMATCH
}					t_return_signal;

/*-----------------------------------------ENV STRUCTURES------------------------------------------------*/

typedef struct s_env
{
	char			*name;
	char			*value;
	unsigned int export : 2;
	struct s_env	*next;
}					t_env;

typedef struct s_env_table
{
	t_env			*table[HASH_TABLE_SIZE];
}					t_env_table;

extern t_env_table	*g_env_table;

/*--------------------------------------EXECUTION ERRORS---------------------------------------------------*/

typedef enum e_error_value
{
	SUCCESS, // Indica que la operación fue exitosa
	ERROR,   // Indica que ocurrió un error
	EMPTY    // Indica que no hay datos
}					t_error_value;

typedef struct builtins
{
	char *name;                               // Nombre del comando o built-in
	int (*f)(int argc, char **args, int out);
		// Puntero a función que implementa el comando
}					t_builtins;

/*--------------------------------------COLORS STRUCT-------------------------------------------------------*/

// reset color:
# define COLOR_RESET "\033[0m"

// Background
# define COLOR_BACKGROUND_BLACK "\033[40m"
# define COLOR_BACKGROUND_RED "\033[41m"
# define COLOR_BACKGROUND_GREEN "\033[42m"
# define COLOR_BACKGROUND_YELLOW "\033[43m"
# define COLOR_BACKGROUND_BLUE "\033[44m"
# define COLOR_BACKGROUND_MAGENTA "\033[45m"
# define COLOR_BACKGROUND_CYAN "\033[46m"
# define COLOR_BACKGROUND_WHITE "\033[47m"
# define COLOR_BACKGROUND_GRAY "\033[100m"

// Text Colors:
# define COLOR_BLACK_TEXT "\033[30m"
# define COLOR_RED_TEXT "\033[31m"
# define COLOR_GREEN_TEXT "\033[32m"
# define COLOR_YELLOW_TEXT "\033[33m"
# define COLOR_BLUE_TEXT "\033[34m"
# define COLOR_MAGENTA_TEXT "\033[35m"
# define COLOR_CYAN_TEXT "\033[36m"
# define COLOR_WHITE_TEXT "\033[37m"
# define COLOR_GRAY_TEXT "\033[90m"

/*
** Bold Text Colors
*/
# define COLOR_BOLD_BLACK_TEXT "\033[30;01m"
# define COLOR_BOLD_RED_TEXT "\033[31;01m"
# define COLOR_BOLD_GREEN_TEXT "\033[32;01m"
# define COLOR_BOLD_YELLOW_TEXT "\033[33;01m"
# define COLOR_BOLD_BLUE_TEXT "\033[34;01m"
# define COLOR_BOLD_MAGENTA_TEXT "\033[35;01m"
# define COLOR_BOLD_CYAN_TEXT "\033[36;01m"
# define COLOR_BOLD_WHITE_TEXT "\033[37;01m"
# define COLOR_BOLD_GRAY_TEXT "\033[90;01m"

/*-------------------------------------LEXER STRUCT--------------------------------------------------------------*/

typedef enum e_foreach_option
{
	FOREACH_WHILE_CONDITION_TRUE,   // Itera mientras la condición sea verdadera
	FOREACH_WHILE_CONDITION_FALSE, 
		// Itera mientras la condición no sea verdadera
	FOREACH_ADVANCE_ITERATOR,       // Avanza el iterador en cada paso
	FOREACH_DO_NOT_ADVANCE_ITERATOR // No avanza el iterador
}					t_foreach_option;

typedef enum e_error_code
{
	ERROR_UNKNOWN,                      // Error desconocido o no clasificado
	ERROR_UNSUPPORTED_FEATURE,          // Característica no soportada
	ERROR_UNSUPPORTED_FEATURE_AND,      // Característica no soportada para '&&'
	ERROR_UNSUPPORTED_FEATURE_OR,       // Característica no soportada para '||'
	ERROR_UNSUPPORTED_FEATURE_SUBSHELL,
		// Característica no soportada para subshells
	ERROR_UNSUPPORTED_FEATURE_HEREDOC, 
		// Característica no soportada para heredoc
	ERROR_GNL                          
		// Error en la función Get Next Line (GNL)
}					t_error_code;

typedef enum e_debug_option
{
	DEBUG_PRINT_CHARACTER_TYPE,  // Imprime el tipo de carácter
	DEBUG_RETURN_CHARACTER_TYPE, // Devuelve el tipo de carácter
	DEBUG_PRINT_POSITION,        // Imprime la posición actual
	DEBUG_START_PROCESS,         // Marca el inicio del proceso
	DEBUG_PRINT_POSITION_ONLY    // Marca y muestra solo la posición
}					t_debug_option;

typedef struct s_lexer
{
	char *current_line;   // Línea actual que se está analizando
	int line_length;      // Longitud de la línea
	int start_index;      // Índice de inicio para el análisis
	int current_position; // Posición actual en la línea
	char previous_char;   // Carácter anterior al actual
	char current_char;    // Carácter actual que se está analizando
	char line_start_char; // Carácter de inicio para el análisis de la línea
}					t_lexer;

typedef enum e_character_type
{
	CHAR_TYPE_ERROR = 0x0,              // Error en el carácter
	CHAR_TYPE_END_OF_TEXT = 0x1,        // Fin de texto
	CHAR_TYPE_WHITESPACE = 0x2,         // Espacio en blanco
	CHAR_TYPE_WORD = 0x4,               // Carácter que pertenece a una palabra
	CHAR_TYPE_LEFT_PARENTHESIS = 0x8,   // Paréntesis izquierdo
	CHAR_TYPE_RIGHT_PARENTHESIS = 0x10, // Paréntesis derecho
	CHAR_TYPE_REDIRECTION_IN = 0x20,    // Redirección de entrada
	CHAR_TYPE_REDIRECTION_OUT = 0x40,   // Redirección de salida
	CHAR_TYPE_SINGLE_QUOTE = 0x80,      // Comillas simples
	CHAR_TYPE_DOUBLE_QUOTE = 0x100,     // Comillas dobles
	CHAR_TYPE_LOGICAL_AND = 0x200,      // Operador lógico '&&'
	CHAR_TYPE_PIPE = 0x400,             // Operador '|' (pipe)
	CHAR_TYPE_SEMICOLON = 0x800,        // Punto y coma
	CHAR_TYPE_PASS = 0x1000,            // Carácter de paso o ignorado
	CHAR_TYPE_DOLLAR = 0x2000,          // Signo de dólar '$'
	CHAR_TYPE_BACKSLASH = 0x4000,       // Barra invertida '\'
	CHAR_TYPE_NONE = 0x8000             // Ningún tipo de carácter específico
}					t_character_type;

extern t_character_type g_token_ascii_table[255];
	// Tabla de mapeo de caracteres ASCII a tipos de caracteres

/*---------------------------------------ENV FILES------------------------------------------------------*/

void				ft_env2hashtable(char **env, t_hashtable *hashtable,
						int array_len);
t_hashtable			*ft_create_envhash(char **env);
void				ft_print_env(t_hashtable *env_hashtable, int is_export);

/*------------------------------------EXECUTION FILES------------------------------------------------------*/

int					xecho(int argc, char **args, int out);
int					xpwd(int argc, char **args, int out);
int					xexit(int argc, char **args, int out);
int					xcd(int argc, char **args, int out);
char				**env_to_arr(t_env *trav);
void				sig_exec(int signo);
char				**convert_to_arr(t_token *args, int ac);
char				**check_cmd(t_ast_node *cmd, int *ac, int *type);
int					launch(t_ast_node *cmd, char **av);
int					execute_fork(t_ast_node *cmd, int out);
int					execute_simple(t_ast_node *cmd);
char				*get_path(char *command, int *err);

/*-------------------------------------LEXER FILES---------------------------------------------------------------*/

void				print_prompt(int sloc);
t_lexer				*lexer__new(int sloc);
void				lexer__del(t_lexer **lex);
int					lexer__error(int opt, t_lexer *lex);
int					lexer__istype(t_lexer *lex, t_character_type type);
int					lexer__istype_start(t_lexer *lex, t_character_type type);
char				lexer__peek(t_lexer *lex);
int					lexer__isword(t_lexer *lex);
int					lexer__isquote(t_lexer *lex);
int					lexer__advance(t_lexer *lex, int n);
int					lexer__pass_quotes(t_lexer *lex, t_character_type type);
t_token				*lexer__token_grabber(t_lexer *lex, t_token_type_key type);
int					lexer__refill_line(t_lexer *lex, int sloc);
t_token				*lexer__get_next_token(t_lexer *lex);
void				lexer__set_start_pos(t_lexer *lex, int new_pos);
int					unsupported_feature(t_lexer *lex, int *type, char curr,
						char next);
int					lexer__deftoken_double(t_lexer *lex, int *len, char curr,
						char next);
int					lexer__isdefined_token(t_lexer *lex, int adv);

#endif
