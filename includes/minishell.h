/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:19:12 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/07/21 14:11:23 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
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

/*PARSING*/
void				ft_free_rlist(t_redir *redir_list);
void				ft_free_tree_val(char **value);
void				ft_free_tree_node(t_ast *ast_node);
void				ft_free_tree(t_ast *ast_tree);
int					ft_count_element(t_token *token_list);
t_ast				*ft_malloc_node(int nb_element);
int					ft_is_redir(int token_type);
t_ast				*ft_create_tree_node(t_token *token_list, int nb_element);
t_ast				*ft_create_tree(t_token *token_list);
t_redir				*ft_init_rnode(int token_type);
t_redir				*ft_add_rnode(t_redir *redir_list, t_token *token_list);


#endif
