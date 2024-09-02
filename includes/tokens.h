#ifndef TOKENS_H
# define TOKENS_H
# include "minishell.h"
# define NUM_DEFINED_TOKENS 19

typedef enum e_token_type
{
	TYPE_PIPE,
	TYPE_SEMICOLON,
	TYPE_DOUBLE_QUOTE,
	TYPE_LEFT_PAREN,
	TYPE_NONE,
    TYPE_ERR,
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
	TOKEN_ERR = 0x0,
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

extern t_token		g_defined_tokens[NUM_DEFINED_TOKENS];
extern t_token_string	g_token_str[NUM_DEFINED_TOKENS];
extern t_token_map		g_token_map[NUM_DEFINED_TOKENS];

t_token					*token__new(t_token_type_key type, char *value, int pos);
t_token					*token__copy(t_token *token);
void					token__del(t_token **token);
void					token__list_del(t_token **token);
int						token__istype(t_token *token, t_token_type_key type);
int						token__iseot(t_token *token);
int						token__isword(t_token *token);
int						token__issep(t_token *token);
int						token__isredir(t_token *token);
int						token__isparenthesis(t_token *token);
void					token__print(t_token *t);

#endif