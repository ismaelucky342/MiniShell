/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:00:20 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 14:34:49 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "Tokenizer.h"
# include "minishell.h"
# include "tokens.h"
/*----------------------------AST STRUCTURES AREA-------------------------*/
/*============================UTILS================================*/

// ast error code

typedef enum err_code
{
	BAD_TOKEN
}						t_err_code;

// node type

typedef enum node_type
{
	CMD,
	SEPARATOR
}						t_ast_node_type;

// ast tokens
typedef enum ast_tokens
{
	ASTREDIR,
	ASTSEPARATOR,
	ASTWORDS
}						t_ast_tokens;

typedef enum clean_node
{
	CLEAN_NODE,
	CLEAN_NODE_AND_CHILDS
}						t_clean_node;

/*-------------------------AST MAIN STRUCTURE----------------------*/

typedef struct ast_ast_node
{
	struct ast_ast_node	*parent;
	struct ast_ast_node	*left;
	struct ast_ast_node	*right;
	size_t				type;
	t_token				*av;
	t_token				*redirections;
	t_token				*files;
	int					stdin;
	int					stdout;
	int					pid;
	t_token				*separators;
	int					pipe_ltor[2];
}						t_ast_node;

typedef struct s_astb
{
	t_ast_node			*ast_tree;
	t_tokenizer			*ast_tokenizer;
	t_token				*current_token;
	t_token				*previous_token;
	t_ast_node			*tree_possition;
}						t_astb;

/*--------------------------INTERPRETER AST PIPES-----------------------------*/

// Definiciones de descriptores de archivo para pipes y estándares
# define PIPE_READ_END 0
# define PIPE_WRITE_END 1
# define STDIN_FILENO 0
# define STDOUT_FILENO 1

// Estructura para almacenar la información
// de los pipes en una lista doblemente enlazada
typedef struct s_pipe_node
{
	struct s_pipe_node	*next;
	struct s_pipe_node	*prev;
	int					pipe_fds[2];
	// Descriptores del pipe
}						t_pipe_node;

// Estructura para almacenar los identificadores
// de procesos en una lista doblemente enlazada
typedef struct s_pid_node
{
	struct s_pid_node	*next;
	struct s_pid_node	*prev;
	int					process_id;
}						t_pid_node;

// Opciones para la interpretación del árbol de sintaxis abstracta (AST)
typedef enum e_ast_interpreter_status
{
	AST_INTERPRETER_SUCCESS,
	AST_INTERPRETER_FAILURE
}						t_ast_interpreter_status;

// Errores posibles durante la interpretación del AST
typedef enum e_ast_interpreter_error
{
	AST_INTERPRETER_ERROR_OPEN,
	AST_INTERPRETER_ERROR_PIPE
}						t_ast_interpreter_error;

// Opciones binarias para operaciones específicas
// Opción para obtener (get)
// Opción para liberar (free)
// Opción para cerrar (close)
// Opción para esperar (wait)
// Opción para agregar (add)
typedef enum e_binary_option
{
	BIN_OPT_ADD = 0x1,
	BIN_OPT_WAIT = 0x2,
	BIN_OPT_CLOSE = 0x4,
	BIN_OPT_FREE = 0x8,
	BIN_OPT_GET = 0x10
}						t_binary_option;

/*-------------------------AST FILES-----------------------*/
int						coincidence(t_astb *tool, t_token_type_key type,
							t_mem_context *ctx);
int						insert_into_node(t_astb *tool, t_token **tokendest,
							t_ast_tokens type, t_mem_context *ctx);
void					node_source(t_astb *tool, t_ast_node *node);
void					find_for_node(t_astb *tool, t_ast_node *node,
							t_token_type_key type);
int						insert_node(t_astb *tool, t_ast_node *node);

int						proc_next(t_astb *tool, t_ast_node **sep,
							t_mem_context *ctx);
int						process(t_astb *tool, t_mem_context *ctx);
int						ft_tree_build_error(t_astb *tool, int opt);
t_ast_node				*ft_node_new(t_ast_node_type type, t_mem_context *ctx);
void					ft_node_delete(t_ast_node **node, int opt,
							t_mem_context *ctx);
t_ast_node				*ast_builder(int sloc, t_mem_context *ctx,
							t_hashtable *env_hashtable);
int						init_tool(t_astb *tool, int sloc, t_mem_context *ctx,
							t_hashtable *env_hashtable);

/*---------------------AST INTERPRETER FILES--------------------*/
/*
int						astTOKEN_error(char *name, int opt);
int						ast_cmd_controller(t_ast_node *cmd);
int						ast_controller(t_ast_node *node);
int						ast_interpreter(t_ast_node *ast);
int						ast_dbl_and_handle(t_ast_node *cmd_sep);
int						ast_dbl_or_handle(t_ast_node *cmd_sep);
int						ast_semicon_handle(t_ast_node *cmd_sep);
int						ast_sep_controller(t_ast_node *sep);
int						ast_parent_ispipe(t_ast_node *node);
int						waitallpipes(int pipe[2], int opt);
int						pid_save(int pid, int opt);
int						ast_pipe_handle(t_ast_node *ppln);
int	redir_handle__each(t_ast_node *cmd, t_token *tmp_redir,
		t_token *tmp_file);
int						redir_handle(t_ast_node *cmd);
*/

#endif