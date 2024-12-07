### 1. **Inicialización**

- **`init.c` y `minishell.c`**: Estas funciones se encargan de la configuración inicial de la minishell (`init_mini`) y la carga del entorno (`ft_env_build` y `ft_h_fill`). También se configura el prompt (`ft_prompt`).
- **`signals.c`**: Configura los manejadores de señales (`ft_set_signal_handlers`) para capturar señales como `Ctrl-C` y `Ctrl-D`, las cuales deben manejarse durante la ejecución interactiva.

### 2. **Entrada y Tokenización**

- **`input.c` y `tokenizer.c`**: Captura y tokeniza la línea de comando ingresada. `tokenizer` divide la línea en tokens y clasifica el tipo de cada uno en función de sus caracteres y delimitadores.
- **`retokenizer.c`**: Reestructura los tokens en casos donde se necesita separar o agrupar tokens para evitar errores de interpretación.

### 3. **Verificación Sintáctica**

- **`checker.c`, `checker_errors.c`, `Errors_1.c`, `Errors_2.c`**: Verifica que la entrada esté sintácticamente correcta, revisando redirecciones, comillas, y estructuras lógicas (`&&`, `||`, `|`, etc.). Si encuentra errores, llama a funciones de manejo de errores (`ft_syntax_error`, `ft_quote_error`, etc.).

### 4. **Construcción del AST**

- **`ast_tree.c`**: Organiza los tokens en un árbol AST (`t_ast_tree`) que representa la estructura jerárquica de los comandos, pipes, y redirecciones. El AST facilita la ejecución en orden y con las prioridades adecuadas.

### 5. **Manejo de `heredoc`**

- **`heredoc.c`, `check_heredoc.c`**: Prepara y verifica el contenido de `heredoc`, donde se espera hasta recibir una entrada coincidente con la palabra clave de finalización. Esta entrada se expande (`ft_expand_str_heredoc`) y se almacena temporalmente para usarse durante la ejecución.

### 6. **Expansión de Variables y Comodines**

- **`expander.c`, `expand_types.c`, `ft_expand_str_env.c`, `heredoc_expander.c`, `wildcard_expand.c`, `wildcards.c`, `wildcards_utils.c`, `wildcards_files.c`**: Realiza la expansión de variables (`$VAR`), reemplazándolas con su valor. También maneja la expansión de comodines, generando listas de archivos que coinciden con patrones como ``.
Es importante que la expansión se realize dentro de cada subproceso (o builtin) de cada comando, para minimizar errores.

### 7. **Ejecución de Comandos**

- **`ft_exec_and_wait.c` y `path_finder.c`**: Ejecuta los comandos en el árbol AST. Primero, intenta ejecutar comandos internos, y luego busca en el sistema los binarios correspondientes (`extract_exec_path`).
- **`ft_execbuiltin.c`**: Si el comando es un builtin, lo ejecuta directamente sin buscar un binario externo.
- **Redirección**: Las funciones en `redirect_utils` (como `ft_open`, `ft_close`, y `ft_dup2`) gestionan la apertura, cierre, y duplicación de archivos y `heredoc`.

### 8. **Limpieza y Manejo de Historial**

- **`cleanup.c`, `ft_free_list.c`, `ft_free_redirections.c`, `ft_free_tree.c`**: Libera la memoria asignada para tokens, el árbol AST, y estructuras de redirección.
- **`history.c`**: Gestiona el historial de comandos, agregando nuevas entradas y guardándolas si es necesario.

### Orden Resumido

El orden general de estos archivos y sus funcionalidades en el flujo es:

1. **Inicialización** (`init.c`, `minishell.c`, `signals.c`)
2. **Entrada y Tokenización** (`input.c`, `tokenizer.c`, `retokenizer.c`)
3. **Verificación Sintáctica** (`checker.c`, `checker_errors.c`, `Errors_1.c`, `Errors_2.c`)
4. **Expansión** (`expander.c`, `expand_types.c`, `ft_expand_str_env.c`, `heredoc_expander.c`, `wildcard_expand.c`)
5. **Construcción del AST** (`ast_tree.c`)
6. **Manejo de `heredoc`** (`heredoc.c`, `check_heredoc.c`)
7. **Ejecución** (`ft_exec_and_wait.c`, `path_finder.c`, `ft_execbuiltin.c`, `redirect_utils.c`)
8. **Limpieza y Historial** (`cleanup.c`, `ft_free_list.c`, `history.c`)



# COSAS QUE FALTAN 
- echo $PATH:"$Carlos":$USER
- PWD auxiliar
- PROTEGER MALLOCS (capullo)
- Arreglar las strings en stack devueltas por ft_get_from_env (y, si hubiese más returns con solo una string en stack, por el amor de dios, esas también...). No hay forma de distinguir en cual se ha hecho malloc y en cual no.
- pwd ha dejado de existir