#ifndef SLEXER_H
# define SLEXER_H
#include "minishell.h"
#include "tokens.h"
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
	CHAR_TYPE_SPACE = 0x2,         // Espacio en blanco
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