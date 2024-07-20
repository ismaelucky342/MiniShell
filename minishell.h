/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:19:12 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/07/20 22:01:11 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 3000

typedef struct s_element
{
	char			*key;
	char			*value;
}					t_element;

typedef struct s_hashtable
{
	t_element		**element_array;
	int				length;
}					t_hashtable;

enum				e_node_type
{
	NODE_CMD = 0,
	NODE_PIPE,
};

enum				e_redir_type
{
	REDIR_OUT = 0,
	REDIR_APPEND_OUT,
	REDIR_IN,
	REDIR_HEREDOC,
};

typedef struct s_redir
{
	char			*value;
	int				redir_type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_ast
{
	char			**value;
	t_redir			*redir_list;
	int				node_type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

enum				e_char_type
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_DOLLER = '$',
	CHAR_S_QUOTE = 39,
	CHAR_D_QUOTE = '"',
};

enum				e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_GREATER,
	TOKEN_GREATGREATER,
	TOKEN_LESSER,
	TOKEN_LESSLESSER,
};

typedef struct s_token
{
	char			*value;
	int				token_type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

extern int			g_exit_code;


#endif
