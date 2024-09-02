#ifndef AST_H
# define AST_H
# include "minishell.h"
# include "slexer.h"
# include "tokens.h"
/*------------------------------------------AST STRUCTURES AREA--------------------------------------------------*/

/*===============================================UTILS============================================================*/

// ast error code

typedef enum err_code
{
	BAD_TOKEN
}					t_err_code;

// node type

typedef enum node_type
{
	CMD,
	SEPARATOR
}					t_ast_node_type;

// ast tokens
typedef enum ast_tokens
{
	ASTREDIR,
	ASTSEPARATOR,
	ASTWORDS
}					t_ast_tokens;

typedef enum clean_node
{
	CLEAN_NODE,
	CLEAN_NODE_AND_CHILDS
}					t_clean_node;

/*-----------------------------------------------AST MAIN STRUCTURE----------------------------------------------------*/

typedef struct ast_ast_node
{
	struct ast_ast_node	*Father;
	struct ast_ast_node	*left;
	struct ast_ast_node	*right;
	size_t			type;
	t_token			*av;
	t_token			*redirections;
	t_token			*files;
	int				stdin;
	int				stdout;
	int				pid;
	t_token			*separators;
	int				pipe_ltor[2];
}					t_ast_node;

typedef struct s_astb
{
	t_ast_node		*ast_tree;
	t_lexer			*ast_lexer;
	t_token			*current_token;
	t_token			*previous_token;
	t_ast_node		*tree_possition;
}					t_astb;

/*-----------------------------------------------INTERPRETER AST PIPES----------------------------------------------------*/

// Definiciones de descriptores de archivo para pipes y estándares
# define PIPE_READ_END 0 // Descriptor para leer desde el pipe
# define PIPE_WRITE_END 1 // Descriptor para escribir en el pipe
# define STDIN_FILENO 0 // Descriptor para la entrada estándar
# define STDOUT_FILENO 1 // Descriptor para la salida estándar

/*
** Descripción del uso de pipes entre procesos:
**
** Para el proceso hijo:
** - Lee desde `fd[STDIN_FILENO][PIPE_READ_END]`.
** - Escribe en `fd[STDOUT_FILENO][PIPE_WRITE_END]`.
**
** Para el proceso padre:
** - Lee desde `fd[STDOUT_FILENO][PIPE_READ_END]`.
** - Escribe en `fd[STDIN_FILENO][PIPE_WRITE_END]`.
**
** Aunque puede parecer extraño para el padre,
	facilita la gestión del pipe en el hijo.
*/

// Estructura para almacenar la información de los pipes en una lista doblemente enlazada
typedef struct s_pipe_node
{
	struct s_pipe_node *next; // Apunta al siguiente nodo en la lista
	struct s_pipe_node *prev; // Apunta al nodo anterior en la lista
	int pipe_fds[2];         
		// Descriptores del pipe (pipe_fds[0] para lectura,pipe_fds[1] para escritura)
}					t_pipe_node;

// Estructura para almacenar los identificadores de procesos en una lista doblemente enlazada
typedef struct s_pid_node
{
	struct s_pid_node *next; // Apunta al siguiente nodo en la lista
	struct s_pid_node *prev; // Apunta al nodo anterior en la lista
	int process_id;          // Identificador del proceso (PID)
}					t_pid_node;

// Opciones para la interpretación del árbol de sintaxis abstracta (AST)
typedef enum e_ast_interpreter_status
{
	AST_INTERPRETER_SUCCESS, // Interpretación exitosa del AST
	AST_INTERPRETER_FAILURE  // Fallo en la interpretación del AST
}					t_ast_interpreter_status;

// Errores posibles durante la interpretación del AST
typedef enum e_ast_interpreter_error
{
	AST_INTERPRETER_ERROR_OPEN, // Error al abrir un recurso
	AST_INTERPRETER_ERROR_PIPE  // Error en la operación del pipe
}					t_ast_interpreter_error;

// Opciones binarias para operaciones específicas
typedef enum e_binary_option
{
	BIN_OPT_ADD = 0x1,   // Opción para agregar (add)
	BIN_OPT_WAIT = 0x2,  // Opción para esperar (wait)
	BIN_OPT_CLOSE = 0x4, // Opción para cerrar (close)
	BIN_OPT_FREE = 0x8,  // Opción para liberar (free)
	BIN_OPT_GET = 0x10   // Opción para obtener (get)
}					t_binary_option;


/*---------------------------------------AST FILES------------------------------------------*/

int					add_token_into_node(
	t_astb *tool, t_token **tokendest, t_ast_tokens type);
void				set_root_to_node(t_astb *tool, t_ast_node *node);
void				search_place_node(
	t_astb *tool, t_ast_node *node, t_token_type_key type);
int					add_to_ast(t_astb *tool, t_ast_node *node);
int					eat(t_astb *tool, t_token_type_key type);
int					process_call_next(t_astb *tool, t_ast_node **sep);
int					process(t_astb *tool);
int					astb_error(t_astb *tool, int opt);
t_ast_node				*node__new(t_ast_node_type type);
void				node__del(t_ast_node **node, int opt);
int					init_tool(t_astb *tool, int sloc);
t_ast_node				*ast_builder(int sloc);


/*---------------------------------------AST INTERPRETER FILES------------------------------*/

int						astTOKEN_error(char *name, int opt);
int						node__cmd_controller(t_ast_node *cmd);
int						node__controller(t_ast_node *node);
int						ast_interpreter(t_ast_node *ast);
int						node__dbl_and_handle(t_ast_node *cmd_sep);
int						node__dbl_or_handle(t_ast_node *cmd_sep);
int						node__semicon_handle(t_ast_node *cmd_sep);
int						node__sep_controller(t_ast_node *sep);
int						node__parent_ispipe(t_ast_node *node);
int						waitallpipes(int pipe[2], int opt);
int						pid_save(int pid, int opt);
int						node__pipe_handle(t_ast_node *ppln);
int						redir_handle__each(
	t_ast_node *cmd, t_token *tmp_redir, t_token *tmp_file);
int						redir_handle(t_ast_node *cmd);



#endif