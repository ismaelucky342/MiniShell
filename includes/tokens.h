/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:58:27 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:24:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include "minishell.h"
# define NUM_DEFINED_TOKENS 19
extern unsigned int		g_exit;
extern int 				g_reset;

typedef enum e_token_type
{
	TYPE_PIPE,
	TYPE_SEMICOLON,
	TYPE_DOUBLE_QUOTE,
	TYPE_LEFT_PAREN,
	TYPE_NONE,
	TYPE_ERROR,
	TYPE_END_TOKEN,
	TYPE_SPACE,
	TYPE_RIGHT_PAREN,
	TYPE_LOGICAL_OR,
	TYPE_BACKSLASH,
	TYPE_DOLLAR,
	TYPE_IGNORE,
	TYPE_WORD,
	TYPE_SINGLE_QUOTE,
	TYPE_REDIR_INPUT,
	TYPE_REDIR_OUTPUT,
	TYPE_DBL_REDIR_OUTPUT,
	TYPE_LOGICAL_AND,
}						t_token_type;

typedef enum e_token_type_key
{
	TOKEN_ERROR = 0x0,
	TOKEN_RIGHT_PAREN = 0x80,
	TOKEN_REDIR_INPUT = 0x100,
	TOKEN_SEMICOLON = 0x8000,
	TOKEN_END_TOKEN = 0x1,
	TOKEN_SPACE = 0x2,
	TOKEN_IGNORE = 0x4,
	TOKEN_WORD = 0x8,
	TOKEN_SINGLE_QUOTE = 0x10,
	TOKEN_DOUBLE_QUOTE = 0x20,
	TOKEN_LEFT_PAREN = 0x40,
	TOKEN_BACKSLASH = 0x10000,
	TOKEN_DOLLAR = 0x40000,
	TOKEN_REDIR_OUTPUT = 0x200,
	TOKEN_DBL_REDIR_OUTPUT = 0x400,
	TOKEN_LOGICAL_AND = 0x800,
	TOKEN_LOGICAL_OR = 0x2000,
	TOKEN_PIPE = 0x4000,
	TOKEN_NONE = 0x200000
}						t_token_type_key;

typedef struct s_token
{
	struct s_token		*next;
	struct s_token		*prev;
	t_token_type_key	type;
	char				*value;
	int					length;
	int					position_in_line;
}						t_token;

typedef struct s_token_string
{
	t_token_type_key	type;
	char				str[20];
}						t_token_string;

typedef struct s_token_map
{
	t_token_type_key	mask;
	t_token_type		idx;
}						t_token_map;

extern t_token			g_defined_tokens[NUM_DEFINED_TOKENS];
extern t_token_string	g_token_str[NUM_DEFINED_TOKENS];
extern t_token_map		g_token_map[NUM_DEFINED_TOKENS];

t_token					*ft_token_new(t_token_type_key type, char *value, int pos,
							t_mem_context *ctx);
t_token					*ft_token_copy(t_token *token, t_mem_context *ctx);
void					ft_token_del(t_token **token, t_mem_context *ctx);
void					ft_token_list_del(t_token **token, t_mem_context *ctx);
int						ft_token_istype(t_token *token, t_token_type_key type);
int						ft_token_iseot(t_token *token);
int						ft_token_isword(t_token *token);
int						ft_token_issep(t_token *token);
int						ft_token_isredir(t_token *token);
int						ft_token_isparenthesis(t_token *token);
void					ft_token_print(t_token *t);

#endif