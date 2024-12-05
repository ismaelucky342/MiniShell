/*
NECESARIO PARA PROCESAR EL ARBOL:

ft_execution

- Núcleo de la ejecución. 
- Primero,
	realiza un backup de los fd estándar (stdin y stdout) para restaurarlos después de la ejecución.

ft_execute_ast 
- para ejecutar la lista de comandos (pipes o comandos simples).
- Luego,
	llama a ft_wait para esperar a que todos los procesos terminen y obtiene el código de salida del proceso correspondiente.
- Restauran los descriptores estándar después de la ejecución.
- Este proceso gestiona la señalización y el estado de la minishell (e.g.,
		g_is_exec).

ft_wait
- Este ciclo espera a que todos los procesos hijos (creados con fork) finalicen. Utiliza waitpid para monitorear los procesos.
- Evalúa el código de salida: si el proceso termina normalmente, 
- obtiene el código de salida con WEXITSTATUS; 
- si el proceso es terminado por una señal,
	obtiene el código de la señal con WTERMSIG + 128.


ft_first_cmd, ft_mid_cmd y ft_last_cmd

- Estas funciones gestionan la ejecución de los primeros,
	intermedios y últimos comandos en una secuencia de pipes.
- Realizan la configuración necesaria para redirecciones y pipes,
	abriendo archivos si es necesario.
- Si el comando es un builtin,
	se ejecuta directamente; si es un comando externo,
	se busca su ruta y se usa execve para ejecutarlo en un proceso hijo.

ft_fork:
- Encargada de crear un proceso hijo. 
- Si fork falla,
	se imprime un error y el programa termina con un código de error.

ft_file_redirs

- Maneja las redirecciones de archivos. Dependiendo del tipo de redirección (entrada o salida),
	abre el archivo correspondiente y realiza la redirección con dup2.

ft_no_path
- Si no se encuentra un comando,
	imprime un mensaje de error y establece el código de salida en 127.
*/

#include "../../includes/minishell.h"

extern int	g_exit;

static int	ft_wait_all(int last_pid, t_tree_node *last)
{
	int	status;
	int	last_exited;
	int	exit_code;

	last_exited = 0;
	exit_code = INT_MIN;
	while (last_exited != -1)
	{
		last_exited = waitpid(-1, &status, 0);
		if (last_exited == last_pid && last_pid != 0)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = WTERMSIG(status) + 128;
		}
	}
	if (exit_code == INT_MIN)
		return (last->exit);
	return (exit_code);
}

static t_tree_node	*ft_interpreter(t_ast_tree *node, t_minishell *boogeyman,
	int *lastpid)
{
	printf("%d\n", node->is_logic);
	if (node->is_logic == TRUE)
		return (ft_logic_interpreter(node, boogeyman, lastpid));
	else
		return (ft_pipes_interpreter(node, boogeyman, lastpid));
}

t_bool	ft_execution(t_ast_tree *tree_nodes, t_minishell *boogeyman)
{
	int				backup[2];
	int				pid;
	int				temp;
	t_tree_node		*last;

	ft_set_signal(1);
	g_exit = 1;
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	last = ft_interpreter(tree_nodes, boogeyman, &pid);
	if (!last)
		return (FALSE);
	temp = ft_wait_all(pid, last);
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
	if (g_exit == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit = 0;
	ft_set_signal(0);
	ft_putstr_fd("\x1b[0m", STDOUT_FILENO);
	if (tree_nodes->cmd_list->is_builtin == 1 && !tree_nodes->cmd_list->next)
        return (tree_nodes->cmd_list->exit);
    return (temp);
}
