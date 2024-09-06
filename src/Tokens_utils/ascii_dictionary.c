/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_dictionary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:46:09 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 10:17:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 Este array etiqueta todos los caracteres ASCII con un 
 código utilizado para agrupar caracteres
 que tienen el mismo sentido (según nuestro léxico).
*/

t_character_type    g_token_dictionary[255] = {
    ['\0'] = CHAR_TYPE_END_OF_TEXT,
    [0x01] = CHAR_TYPE_END_OF_TEXT,
    [0x02] = CHAR_TYPE_PASS,
    [0x03] = CHAR_TYPE_PASS,
    [0x04] = CHAR_TYPE_PASS,
    [0x05] = CHAR_TYPE_PASS,
    [0x06] = CHAR_TYPE_PASS,
    ['\a'] = CHAR_TYPE_PASS,
    ['\b'] = CHAR_TYPE_PASS,
    [0x0e ... 0x1f] = CHAR_TYPE_PASS,
    [0x7f] = CHAR_TYPE_PASS,
    ['\t'] = CHAR_TYPE_SPACE,
    ['\n'] = CHAR_TYPE_SPACE,
    ['\v'] = CHAR_TYPE_SPACE,
    ['\f'] = CHAR_TYPE_SPACE,
    ['\r'] = CHAR_TYPE_SPACE,
    [' '] = CHAR_TYPE_SPACE,
    ['\"'] = CHAR_TYPE_DOUBLE_QUOTE,
    ['\''] = CHAR_TYPE_SINGLE_QUOTE,
    ['('] = CHAR_TYPE_LEFT_PARENTHESIS,
    [')'] = CHAR_TYPE_RIGHT_PARENTHESIS,
    ['&'] = CHAR_TYPE_LOGICAL_AND,
    ['|'] = CHAR_TYPE_PIPE,
    ['<'] = CHAR_TYPE_REDIRECTION_IN,
    ['>'] = CHAR_TYPE_REDIRECTION_OUT,
    ['$'] = CHAR_TYPE_DOLLAR,
    ['*'] = CHAR_TYPE_WORD,
    ['?'] = CHAR_TYPE_WORD,
    [';'] = CHAR_TYPE_SEMICOLON,
    ['0' ... '9'] = CHAR_TYPE_WORD,
    ['a' ... 'z'] = CHAR_TYPE_WORD,
    ['A' ... 'Z'] = CHAR_TYPE_WORD,
    ['!'] = CHAR_TYPE_WORD,
    ['#'] = CHAR_TYPE_WORD,
    ['%'] = CHAR_TYPE_WORD,
    ['+'] = CHAR_TYPE_WORD,
    [','] = CHAR_TYPE_WORD,
    ['-'] = CHAR_TYPE_WORD,
    ['.'] = CHAR_TYPE_WORD,
    [':'] = CHAR_TYPE_WORD,
    ['='] = CHAR_TYPE_WORD,
    ['@'] = CHAR_TYPE_WORD,
    ['['] = CHAR_TYPE_WORD,
    [']'] = CHAR_TYPE_WORD,
    ['^'] = CHAR_TYPE_WORD,
    ['_'] = CHAR_TYPE_WORD,
    ['`'] = CHAR_TYPE_WORD,
    ['{'] = CHAR_TYPE_WORD,
    ['}'] = CHAR_TYPE_WORD,
    ['/'] = CHAR_TYPE_WORD,
    ['~'] = CHAR_TYPE_WORD,
    ['\\'] = CHAR_TYPE_BACKSLASH
};

/*
** Este array g_defined_tokens DEBE estar ordenado exactamente
** como el enum e_token_type
** 'ERR' debe ser el primero y 'NONE' debe ser el último
*/

t_token    g_defined_tokens[NUM_DEFINED_TOKENS] = {
    {NULL, NULL, TOKEN_ERROR, "", 0, 0},
    {NULL, NULL, TOKEN_END_TOKEN, "", 0, 0},
    {NULL, NULL, TOKEN_SPACE, "", 0, 0},
    {NULL, NULL, TOKEN_IGNORE, "", 0, 0},
    {NULL, NULL, TOKEN_WORD, "", 0, 0},
    {NULL, NULL, TOKEN_SINGLE_QUOTE, "\'", 1, 0},
    {NULL, NULL, TOKEN_DOUBLE_QUOTE, "\"", 1, 0},
    {NULL, NULL, TOKEN_LEFT_PAREN, "(", 1, 0},
    {NULL, NULL, TOKEN_RIGHT_PAREN, ")", 1, 0},
    {NULL, NULL, TOKEN_REDIR_INPUT, "<", 1, 0},
    {NULL, NULL, TOKEN_REDIR_OUTPUT, ">", 1, 0},
    {NULL, NULL, TOKEN_DBL_REDIR_OUTPUT, ">>", 2, 0},
    {NULL, NULL, TOKEN_LOGICAL_AND, "&&", 2, 0},
    {NULL, NULL, TOKEN_LOGICAL_OR, "||", 2, 0},
    {NULL, NULL, TOKEN_PIPE, "|", 1, 0},
    {NULL, NULL, TOKEN_SEMICOLON, ";", 1, 0},
    {NULL, NULL, TOKEN_BACKSLASH, "/", 1, 0},
    {NULL, NULL, TOKEN_DOLLAR, "$", 1, 0},
    {NULL, NULL, TOKEN_NONE, "", 0, 0}
};

t_token_string    g_token_str[NUM_DEFINED_TOKENS] = {
    {TOKEN_ERROR, "ERR"},
    {TOKEN_END_TOKEN, "EOT"},
    {TOKEN_SPACE, "SPACE"},
    {TOKEN_IGNORE, "PASS"},
    {TOKEN_WORD, "WORD"},
    {TOKEN_SINGLE_QUOTE, "SQUOTE"},
    {TOKEN_DOUBLE_QUOTE, "DQUOTE"},
    {TOKEN_LEFT_PAREN, "LPAREN"},
    {TOKEN_RIGHT_PAREN, "RPAREN"},
    {TOKEN_REDIR_INPUT, "REDIR_IN"},
    {TOKEN_REDIR_OUTPUT, "REDIR_OUT"},
    {TOKEN_DBL_REDIR_OUTPUT, "DREDIR_OUT"},
    {TOKEN_LOGICAL_AND, "DBL_AND"},
    {TOKEN_LOGICAL_OR, "DBL_OR"},
    {TOKEN_PIPE, "PIPE"},
    {TOKEN_SEMICOLON, "SEMICON"},
    {TOKEN_BACKSLASH, "BSLASH"},
    {TOKEN_DOLLAR, "DOLLAR"},
    {TOKEN_NONE, "NONE"}
};

t_token_map    g_token_map[NUM_DEFINED_TOKENS] =
{

    {TOKEN_ERROR,  TYPE_ERROR},
    {TOKEN_END_TOKEN, TYPE_END_TOKEN},
    {TOKEN_SPACE, TYPE_SPACE},
    {TOKEN_IGNORE, TYPE_IGNORE},
    {TOKEN_WORD, TYPE_WORD},
    {TOKEN_SINGLE_QUOTE, TYPE_SINGLE_QUOTE},
    {TOKEN_DOUBLE_QUOTE, TYPE_DOUBLE_QUOTE},
    {TOKEN_LEFT_PAREN, TYPE_LEFT_PAREN},
    {TOKEN_RIGHT_PAREN, TYPE_RIGHT_PAREN},
    {TOKEN_REDIR_INPUT, TYPE_REDIR_INPUT},
    {TOKEN_REDIR_OUTPUT, TYPE_REDIR_OUTPUT},
    {TOKEN_DBL_REDIR_OUTPUT, TYPE_DBL_REDIR_OUTPUT},
    {TOKEN_LOGICAL_AND, TYPE_LOGICAL_AND},
    {TOKEN_LOGICAL_OR, TYPE_LOGICAL_OR},
    {TOKEN_PIPE, TYPE_PIPE},
    {TOKEN_SEMICOLON, TYPE_SEMICOLON},
    {TOKEN_BACKSLASH, TYPE_BACKSLASH},
    {TOKEN_DOLLAR, TYPE_DOLLAR},
    {TOKEN_NONE, TYPE_NONE}
};

t_token *get_defined_token(t_token_map *token_map, 
            t_token_string *token_str, int index)
{
    if (index < 0 || index >= NUM_DEFINED_TOKENS)
        return NULL;
    return &token_map[index];  
}