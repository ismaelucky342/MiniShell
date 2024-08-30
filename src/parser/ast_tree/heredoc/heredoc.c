#include "../includes/minishell.h"

int heredoc(char *limiter)
{
	int		fd[2];
	char	*line;
	ssize_t limiter_len;

	if (pipe(fd) == -1)
	{
		perror("minishell: Pipe");
		return (-1);
	}

	limiter_len = ft_strlen(limiter);

	while (1)
	{
		line = get_line();
		if (line)
		{
			if (ft_strncmp(line, limiter, limiter_len) == 0 && line[limiter_len] == '\0')
			{
				free(line);
				break;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		else
		{
			write(fd[1], "\n", 1);
			break;
		}
	}
	close(fd[1]);
	return (fd[0]);
}

/*
Función get_line:

La función get_line se encarga de leer una línea de entrada. Usa readline si la entrada es interactiva y get_next_line si no lo es. Esto parece estar bien, pero asegúrate de que get_next_line maneje correctamente la entrada.
Función here_doc:

La función here_doc utiliza un pipe para almacenar la entrada del heredoc. Compara cada línea leída con el delimitador para finalizar la entrada. Es importante que maneje adecuadamente la comparación de cadenas y la escritura en el pipe.
Funciones handle_cmd y handle_redir:

Estas funciones manejan la redirección de entrada para comandos y redirecciones. Asegúrate de que la expansión de variables y la llamada a here_doc se manejen adecuadamente.
Función climb_tree:

La función climb_tree recorre el árbol AST para aplicar la redirección y manejo de heredoc. Asegúrate de que maneje correctamente los nodos del árbol y las operaciones de redirección.
*/