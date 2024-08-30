#include "../includes/minishell.h"

t_token_type t_type_process(const char *string)
{
    if (is_separator(*string))
        return T_SEPARATOR;
    if (!ft_strncmp(string, "&&", 2))
        return T_AND;
    if (!ft_strncmp(string, "||", 2))
        return T_OR;
    if (!ft_strncmp(string, ">>", 2))
        return T_REDIR_APPEND;
    if (!ft_strncmp(string, "<<", 2))
        return T_REDIR_HEREDOC;
    if (!ft_strncmp(string, "(", 1))
        return T_Lparentesis;
    if (!ft_strncmp(string, ")", 1))
        return T_Rparentesis;
    if (!ft_strncmp(string, "|", 1))
            return T_PIPE;
    if (!ft_strncmp(string, ">", 1))
        return T_REDIR_OUT;
    if (!ft_strncmp(string, "<", 1))
        return T_REDIR_IN;
    return T_WORD;
}

t_token *words(char **string, t_token *token_last)
{
    t_token_type token_type = T_WORD;
    int i = 0;
    char quotes = 0;

    while ((token_type == T_WORD || quotes) && (*string)[i])
    {
        if ((*string)[i] == quotes)
            quotes = 0;
        else if (!quotes && ((*string)[i] == '\'' || (*string)[i] == '"'))
        {
            token_last->quotes = 1;
            quotes = (*string)[i];
        }
        token_type = t_type_process((*string) + i);
        i++;
    }
    if (token_type != T_WORD)
        i--;
    if (!token_last || token_last->type != T_WORD)
        token_last = token_add(token_last, T_WORD);
    token_last->value = ft_substr(*string, 0, i);
    *string += i - 1;
    return token_last;
}

t_token *next_token(char *string, t_token *token_last)
{
    t_token_type token_type;
    int i = 0;

    while (string[i] && is_separator(string[i]) && is_separator(string[i + 1]))
        i++;

    token_type = t_type_process(string);
    if (is_separator(string[0]) && !string[1])
        return token_last;

    if (is_separator(string[0]) && is_separator(string[1]))
        return next_token(string + 1, token_last);

    token_last = token_add(token_last, token_type);
    if (token_type == T_WORD)
        token_last = words(&string, token_last);

    i = 1; 
    if (token_type == T_AND || token_type == T_OR ||
        token_type == T_REDIR_APPEND || token_type == T_REDIR_HEREDOC)
        i++;

    if (string[i])
        token_last = next_token(string + i, token_last);

    return token_last;
}



