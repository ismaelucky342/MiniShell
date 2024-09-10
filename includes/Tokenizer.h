/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:17:29 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 12:21:40 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"
# include "tokens.h"

typedef enum e_foreach_option
{
	FOREACH_WHILE_CONDITION_TRUE,
	FOREACH_WHILE_CONDITION_FALSE,
	FOREACH_ADVANCE_ITERATOR,
	FOREACH_DO_NOT_ADVANCE_ITERATOR
}						t_foreach_option;

typedef enum e_error_code
{
	ERROR_UNKNOWN,
	ERROR_UNSUPPORTED_FEATURE,
	ERROR_UNSUPPORTED_FEATURE_AND,
	ERROR_UNSUPPORTED_FEATURE_OR,
	ERROR_UNSUPPORTED_FEATURE_SUBSHELL,
	ERROR_UNSUPPORTED_FEATURE_HEREDOC,
	ERROR_GET_NEXT_LINE
}						t_error_code;

typedef enum e_debug_option
{
	DEBUG_PRINT_CHARACTER_TYPE,
	DEBUG_RETURN_CHARACTER_TYPE,
	DEBUG_PRINT_POSITION,
	DEBUG_START_PROCESS,
	DEBUG_PRINT_POSITION_ONLY
}						t_debug_option;

typedef struct s_tokenizer
{
	char				*current_line;
	int					line_length;
	int					start_index;
	int					current_position;
	char				previous_char;
	char				current_char;
	char				line_start_char;
}						t_tokenizer;

typedef enum e_character_type
{
	CHAR_ERROR = 0x0,
	CHAR_END_OF_TEXT = 0x1,
	CHAR_SPACE = 0x2,
	CHAR_WORD = 0x4,
	CHAR_LEFT_PARENTHESIS = 0x8,
	CHAR_RIGHT_PARENTHESIS = 0x10,
	CHAR_REDIRECTION_IN = 0x20,
	CHAR_REDIRECTION_OUT = 0x40,
	CHAR_SINGLE_QUOTE = 0x80,
	CHAR_DOUBLE_QUOTE = 0x100,
	CHAR_LOGICAL_AND = 0x200,
	CHAR_PIPE = 0x400,
	CHAR_SEMICOLON = 0x800,
	CHAR_PASS = 0x1000,
	CHAR_DOLLAR = 0x2000,
	CHAR_BACKSLASH = 0x4000,
	CHAR_NONE = 0x8000
}						t_character_type;

extern t_character_type	g_token_dictionary[255];

/*-------------------TOKENIZER FILES--------------------*/

t_token					*ft_tokenizer_handle_defined_token(t_tokenizer *tz);
t_token					*ft_tokenizer_get_next_token_part2(t_tokenizer *tz);
t_token					*ft_tokenizer_handle_defined_token(t_tokenizer *tz);
void					print_prompt(int sloc, t_hashtable *env_hashtable);
t_tokenizer				*ft_tokenizer_new(int sloc, t_hashtable *env_hashtable);
void					ft_tokenizer_delete(t_tokenizer **tz);
int						ft_tokenizer_error(int opt, t_tokenizer *tz);
void					handle_error_unknown(t_tokenizer *tz, int code);
void					handle_error_unsupported_feature(t_tokenizer *tz, int code);
void					handle_specific_errors(int opt, int code);
int						ft_tokenizer_istype(t_tokenizer *tz,
							t_character_type type);
int						ft_tokenizer_istype_start(t_tokenizer *tz,
							t_character_type type);
char					ft_tokenizer_peek(t_tokenizer *tz);
int						ft_tokenizer_isword(t_tokenizer *tz);
int						ft_tokenizer_isquote(t_tokenizer *tz);
int						ft_tokenizer_advance(t_tokenizer *tz, int n);
int						ft_tokenizer_pass_quotes(t_tokenizer *tz,
							t_character_type type);
t_token					*ft_tokenizer_token_grabber(t_tokenizer *tz,
							t_token_type_key type);
int						ft_tokenizer_refill_line(t_tokenizer *tz, int sloc,
							t_hashtable *env_hashtable);
t_token					*ft_tokenizer_get_next_token(t_tokenizer *tz);
void					ft_tokenizer_set_start_pos(t_tokenizer *tz,
							int new_pos);
int						unsupported_feature(t_tokenizer *tz, int *type,
							char curr, char next);
int						ft_tokenizer_deftoken_double(t_tokenizer *tz, int *len,
							char curr, char next);
int						ft_isdefined_token(t_tokenizer *tz, int adv);

#endif