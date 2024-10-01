/*
NECESARIO PARA PROCESAR EL ARBOL:

ft_execution

- Núcleo de la ejecución. 
- Primero, realiza un backup de los fd estándar (stdin y stdout) para restaurarlos después de la ejecución.

ft_execute_ast 
- para ejecutar la lista de comandos (pipes o comandos simples).
- Luego, llama a ft_wait para esperar a que todos los procesos terminen y obtiene el código de salida del proceso correspondiente.
- Restauran los descriptores estándar después de la ejecución.
- Este proceso gestiona la señalización y el estado de la minishell (e.g., g_is_exec).

ft_wait
- Este ciclo espera a que todos los procesos hijos (creados con fork) finalicen. Utiliza waitpid para monitorear los procesos.
- Evalúa el código de salida: si el proceso termina normalmente, 
- obtiene el código de salida con WEXITSTATUS; 
- si el proceso es terminado por una señal, obtiene el código de la señal con WTERMSIG + 128.


ft_first_cmd, ft_mid_cmd y ft_last_cmd

- Estas funciones gestionan la ejecución de los primeros, intermedios y últimos comandos en una secuencia de pipes.
- Realizan la configuración necesaria para redirecciones y pipes, abriendo archivos si es necesario.
- Si el comando es un builtin, se ejecuta directamente; si es un comando externo, se busca su ruta y se usa execve para ejecutarlo en un proceso hijo.

ft_fork:
- Encargada de crear un proceso hijo. 
- Si fork falla, se imprime un error y el programa termina con un código de error.

ft_file_redirs

- Maneja las redirecciones de archivos. Dependiendo del tipo de redirección (entrada o salida), abre el archivo correspondiente y realiza la redirección con dup2.

ft_no_path
- Si no se encuentra un comando, imprime un mensaje de error y establece el código de salida en 127.
*/