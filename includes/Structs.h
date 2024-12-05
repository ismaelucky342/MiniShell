/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:46:10 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:00:58 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*===============================INCLUDES AREA==============================*/

# include "../Libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include "minishell.h"

/*===============================DEFINES AREA==============================*/

/*------------------------------MINISHELL MASKS----------------------------*/
# define M_AND_OP 0b1
# define M_OR_OP 0b10
# define M_WAIT 0b100
# define M_INFILE 0b1
# define M_OUT 0b10
# define M_HEREDOC 0b100
# define M_CONCAT_OUT_ST 0b1000

/*------------------------------MINISHELL CONSTS----------------------------*/

# define FILE_REDIR 0
# define PIPE 1
# define LOGIC 2
# define ARG 3
# define E_EXP_ARG 4
# define W_EXP_ARG 5

/*------------------------------MINISHELL MACROS----------------------------*/

# define H_DOC_TMP_BASE "/tmp/.dash_tmp_heredoc_"
# define HIST_TMP_BASE "/.dash_history"
# define HIST_ERROR_MSG "MiniShell: Error creating history file\n"
# define PROMPT_BASE ft_prompt(boogeyman->envp)

# ifndef SIZE_T_MAX
#  define SIZE_T_MAX UINT_MAX
# endif

# ifndef ECHOCTL
#  define ECHOCTL 0000400
# endif

/*=============================STRUCTURES AREA=============================*/

/*------------------------------TOKENS STRUCTS-----------------------------*/

typedef struct s_token
{
	char	*str;
	int		type;
}	t_token;

typedef struct s_redirection_token
{
	char	*file_name;
	char	redir_type;
}	t_redirection_token;

/*------------------------------AST_TREE STRUCTS-----------------------------*/

typedef struct s_tree_node
{
	char				**args;
	char				pipe_out;
	t_list				*redirs_lst;
	struct s_tree_node	*next;
	int					pid;
	int					exit_code;
	char				is_builtin;
	int					pipe_fds[2];
	char				*path;
}	t_tree_node;

typedef struct s_ast_tree
{
	struct s_ast_tree	*left;
	struct s_ast_tree	*right;
	t_list				*cmd_tokens;
	char				*cmd_str;
	char				*expanded_str;
	t_tree_node			*cmd_list;
	char				is_logic;
	int					exit_code;
}	t_ast_tree;

/*------------------------------MINISHELL SUPERSTRUCT--------------------------*/

typedef struct s_minishell
{
	int			history_fd;
	int			last_exit;
	t_ast_tree	*cmd_tree;
	char		**envp;
	long		env_size;
	long		env_elems;
	char		*custom_prompt;
	char		eof;
	char		cont;
}	t_minishell;

#endif
