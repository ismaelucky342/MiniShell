#include "../includes/minishell.h"

char *get_line(void)
{
    char *line;
    char *tmp;

    if (isatty(fileno(stdin)) && !DEBUG)
        line = readline(">");
    else
    {
        tmp = get_next_line(STDIN_FILENO);
        if (tmp)
        {
            line = ft_strtrim(tmp, "\n");
            free(tmp);
        }
        else
            line = NULL;
    }
    return (line);
}
