/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:51:34 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/16 12:26:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include "colors.h"
# include <stdio.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>

/*==============================DEFINES AREA=====================*/

# define PB "\001\x1b[32m\002Minishell\001\x1b[0m\002 - \001\x1b[31m\002"
# define HIST_ERROR_MSG "Minishell: HOME is not set, history unavailable."
# define H_DOC_TMP_BASE "/tmp/.dash_tmp_heredoc_"
# define HIST_TMP_BASE "/.dash_history"
# define FILE_REDIR 0
# define PIPE 1
# define LOGIC 2
# define CONCATOUT_MASK 0b1000
# define OUTFILE_MASK 0b10
# define HEREDOC_MASK 0b100
# define AND_MASK 0b1
# define OR_MASK 0b10
# define WAIT_MASK 0b100

# ifndef SIZE_T_MAX
#  define ARG 3
#  define E_EXP_ARG 4
#  define W_EXP_ARG 5
#  define INFILE_MASK 0b1
#  define SIZE_T_MAX ULONG_MAX
#  define ERROR_MEMORY 2
# endif

typedef int t_bool;
# define OK 0
# define KO 1
# define TRUE 0
# define FALSE 1

/*=============================STRUCTS AREA==========================*/

# ifndef ECHOCTL
#  define ECHOCTL 0000400
# endif

extern int g_exit;

/**
 * @brief Representa un token individual de la entrada.
 *
 * Esta estructura contiene un token de la entrada del usuario,
 * con su contenido y el tipo de token, que puede representar
 * diferentes categorías como palabras, operadores, etc.
 */
typedef struct s_token
{
	char				*str;	/**< Contenido del token como cadena de caracteres */
	int					type;	/**< Tipo de token, que representa diferentes categorías */
}						t_token;

/**
 * @brief Representa un token de redirección en un comando.
 *
 * Contiene el nombre del archivo o dispositivo al que se va a redirigir
 * la entrada o salida del comando y el tipo de redirección, como `>`, `<`, `>>`, o `<<`.
 */
typedef struct s_redirection_token
{
	char				*name;	/**< Nombre del archivo o dispositivo de redirección */
	char				type;	/**< Tipo de redirección, almacenado como carácter */
}						t_redirection_token;

/**
 * @brief Nodo que representa un comando o conjunto de comandos en una tubería.
 *
 * Esta estructura representa un comando individual en el árbol de ejecución,
 * con sus argumentos, redirecciones, y configuración de pipes. También contiene
 * información sobre si es un comando incorporado y el ID del proceso en ejecución.
 */
typedef struct s_tree_node
{
	char				**args;			/**< Argumentos del comando, con el primer argumento siendo el nombre */
	t_bool				pipe_out;		/**< Indicador de si la salida se dirige a un pipe (1 para verdadero, 0 para falso) */
	t_list				*redir_list;	/**< Lista de tokens de redirección asociados con el comando */
	struct s_tree_node	*next;			/**< Puntero al próximo nodo de comando en la misma tubería */
	int					pid;			/**< ID del proceso cuando el comando se ejecuta */
	int					exit;			/**< Código de salida del comando */
	char				is_builtin;		/**< Indicador de si el comando es un comando incorporado en el shell */
	int					pipe_fds[2];	/**< Descriptores de archivo para la tubería si se utiliza redirección */
	char				*path;			/**< Ruta absoluta del ejecutable del comando */
}						t_tree_node;

/**
 * @brief Nodo de árbol de sintaxis abstracta (AST) que representa una estructura de comandos.
 *
 * Este nodo representa una estructura lógica de comandos en un AST, que puede incluir
 * operadores lógicos (como `&&` o `||`), listas de tokens de comandos, y secuencias de comandos.
 * Contiene tanto el comando original como la cadena expandida, además de un subárbol izquierdo
 * y derecho para expresiones complejas.
 */
typedef struct s_ast_tree
{
	struct s_ast_tree	*left;           /**< Subárbol izquierdo, representa la primera parte de una expresión lógica o secuencia de comandos */
	struct s_ast_tree	*right;          /**< Subárbol derecho, representa la segunda parte de una expresión lógica o secuencia de comandos */
	t_list				*cmd_tokens;     /**< Lista de tokens (t_token) del comando en este nodo */
	char				*cmd_str;        /**< Cadena original del comando en este nodo */
	char				*expanded_str;   /**< Cadena del comando después de la expansión de variables y sustituciones */
	t_tree_node			*cmd_list;       /**< Lista de nodos de comandos (t_tree_node) que representan comandos ejecutables */
	t_bool				is_logic;        /**< Indicador de si el nodo representa un operador lógico */
	int					exit;            /**< Código de salida del nodo o del comando ejecutado en este nodo */
}						t_ast_tree;

/**
 * @brief Estructura principal que representa el estado de la minishell durante su ejecución.
 *
 * Contiene información sobre el historial de comandos, el último código de salida,
 * el árbol de comandos actual, el entorno, y otras variables importantes del estado global.
 */

typedef struct s_minishell
{
	int					history_fd;     /**< Descriptor de archivo para el historial de comandos */
	int					last_exit;      /**< Código de salida del último comando ejecutado */
	t_ast_tree			*cmd_tree;      /**< Árbol de comandos actual (AST) */
	char				**envp;         /**< Puntero al entorno de variables de la minishell */
	char				*aux_pwd;		/**< Duplicado del pwd para el builtin pwd. Si PWD existe en el PATH, se usa ese, el duplicado solo existe para cuando ese no exista. */
	long				env_size;       /**< Tamaño del entorno en bytes */
	long				env_elems;      /**< Número de elementos en el entorno */
	char				*ft_prompt;     /**< Prompt personalizado para la shell */
	t_bool				eof;            /**< Indicador de fin de archivo (EOF) */
	t_bool				cont;           /**< Indicador de continuación de comando (por ejemplo, si hay una línea incompleta) */
}						t_minishell;

/*==============================THE HITMAN=========================*/

void		ft_hitman(t_minishell *boogeyman);

/*==============================PARSE AREA=========================*/

void		ft_free_list(t_tree_node *cmd_list);
void		ft_free_redirections(void *t);

int			ft_fill_list(t_list *begin, t_ast_tree *tree_node);
void		*ft_free_ast_tree(t_ast_tree *tree);
char		*dictionary(char *str, int needle_tip);
int			ft_env_build(t_minishell *boogeyman, char *key_val);
char		*get_value_from_env(char **envp, char *key,
				int *exists);
int			ft_remove_env(t_minishell *boogeyman, char *key);
void		ft_env_no_value(t_minishell *boogeyman);

int			ft_heredoc(char **str, int *i, char **f_name);
int			ft_expand_heredoc(int o_fd, t_redirection_token *tok,
				char **envp);
void		new_string(char **str, int j, char *tmp, char *tmp2);
void		heredoc_input(char **line, char *prompt, char *delim,
				int *fd);
char		*get_tmp_filename(void);

void		ft_init_file(t_minishell *boogeyman);
void		ft_h_fill(t_minishell *boogeyman);
void		ft_add_history(char *str, t_minishell *boogeyman);

void		init_minishell(t_minishell *boogeyman, char **envp, int argc,
				char **argv);
char		*ft_prompt(char **env);
t_list		*tokenizer(char *str);
char		ft_is_reserved_char(char c);
void		ft_set_signal_handlers(void);
void		ft_sig_handler(int signum);

void		skip_to_delimiter(char *str, int *i, char delim);
void		skip_spaces(char *str, int *i, int *start, int mode);
int			ft_remove_quotes(t_list *tokens);
void		ft_str_unquote(char *str);

int			retokenize(t_list *curr, int type, int start,
				int *lngths);

char		*ft_wildcards(char *regex);
void		wildcard_expand(t_list *curr, int *i);
void		handle_wildcard(int *conts, char *f_name, char *regex);
int			strlen_and_free(char **tmp, char **tmp2, char **file);
void		get_files(DIR **dir_ptr, struct dirent **directory);
int			regex_iterator(char *regex, char *f_name, int *j,
				int i);
int			strlen_and_free(char **tmp, char **tmp2, char **file);


/*============================EXEC AREA=================================*/

/*
ARBOL DE PRIORIDADES:
1. ()
1. && / ||
2. REDIRS
3. PIPES
*/

t_bool		ft_execution(t_ast_tree *tree_nodes, t_minishell *boogeyman);
t_tree_node	*ft_pipes_interpreter(t_ast_tree *node, t_minishell *boogeyman,
				int *lastpid);

t_bool		ft_exec_single_cmd(t_tree_node *node, t_minishell *boogeyman);
t_bool		exec_first_cmd(t_tree_node *node, t_minishell *boogeyman,
				int *outfd);
t_bool		exec_mid_cmd(t_tree_node *node, t_minishell *boogeyman,
				int *outfd);
t_bool		exec_last_cmd(t_tree_node *node, t_minishell *boogeyman,
				int *outfd);
t_bool		ft_exec_builtin(t_tree_node *node, t_minishell *boogeyman,
				char parent);

int			isbuiltin(char *str);
int			ft_cd(t_tree_node *node, t_minishell *boogeyman);
int			ft_echo(t_tree_node *node, t_minishell *boogeyman);
int			ft_env(t_tree_node *node, t_minishell *boogeyman);
int			ft_exit(t_tree_node *node, t_minishell *boogeyman, char print);
int			ft_export(t_tree_node *node, t_minishell *boogeyman);
int			ft_pwd(t_tree_node *node, t_minishell *boogeyman);
int			ft_unset(t_tree_node *node, t_minishell *boogeyman);

//expander

char		*ft_expand(char *line, char **envp, char expand_all);
int			ft_list_expand(t_list *list, t_minishell *boogeyman);
void		list_expand(t_list *curr, t_minishell *boogeyman);

void		wildcard_expand(t_list *curr, int *i);
void		ft_expand_env(t_list *curr, int *i, int check_w_cards,
				t_minishell *boogeyman);
void		double_quote_expand(t_list *curr, int *i, t_minishell *boogeyman);
void		single_quote_expand(t_list *curr, int *i);

//syntax_checker

int			ft_check_heredoc(t_minishell *boogeyman);
void		ft_syntax_error(char *str);
void		ft_quote_error(void);
void		ft_bracket_error(void);
int			ft_create_heredocs(char **str);
int			ft_check_quotes(char *str);
int			ft_check_brackets(char *str);
int			ft_check_fredirs(char *str);
void		skip_to_delimiter(char *str, int *i, char delim);

//term_settings

int			ft_set_signal(int val);
int			ft_set_echo(int val);

//utils

void		ft_exit_msg(int exit, t_minishell *boogeyman, char print);
void		ft_array_free(char **array);
void		free_cmd_token(void *tok);
char		*get_cwd_str(void);
void		ft_memory_error(t_minishell *boogeyman);
void		ft_tmp(char **tmp, int *chell);
int			ft_check_file(char *str, int *i);

#endif
