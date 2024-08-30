#include "../includes/minishell.h"

int heredoc(char *limiter)
{
    int fd[2];
    char *line;

    if (pipe(fd) == -1)
        return (perror("minishell: Pipe:"), -1);
    
    while (1)
    {
        line = get_line();
        if (line)
        {
            if (*line && !ft_strncmp(line, limiter, ft_strlen(limiter)) && line[ft_strlen(limiter)] == '\0')
            {
                free(line);
                break;
            }
            write(fd[1], line, ft_strlen(line));
            write(fd[1], "\n", 1);
            free(line);
        }
    }
    close(fd[1]);
    return (fd[0]);
}
