/*
ft_is_rel_path (función estática)

Verifica si un path dado es una ruta relativa o absoluta.
Entrada: Una cadena path.
Salida: Devuelve 1 si la ruta es relativa o absoluta, es decir:
Comienza con ./ (ruta relativa en el directorio actual).
Comienza con ../ (ruta relativa en el directorio superior).
Comienza con / (ruta absoluta).
En cualquier otro caso, devuelve 0.
Uso: Determinar si el comando proporcionado por el usuario es una ruta que debe ser interpretada como tal, o si se debe buscar el comando en el PATH.

2. ft_execbuiltin

Ejecuta un comando interno (builtin) de la minishell.
Parámetros:
t_cmd_node *node: Nodo de la lista de comandos que contiene la información del comando a ejecutar.
t_mshell_sack *sack: Estructura que contiene el estado de la shell.
char parent: Indica si el comando es ejecutado en el proceso padre.
Funcionalidad:
Si el comando es ejecutado en el proceso padre (parent es verdadero), se gestionan las redirecciones de archivo mediante ft_file_redirs.
Dependiendo del comando que sea, llama a la función correspondiente para manejarlo:
cd: Cambiar de directorio.
echo: Imprimir mensajes.
exit: Salir de la shell.
pwd: Imprimir el directorio actual.
unset: Eliminar variables de entorno.
export: Exportar variables de entorno.
Si no es el proceso padre, finaliza la ejecución con exit() utilizando el código de salida del comando.
Uso: Ejecuta comandos internos de la shell como cd, echo, exit, etc.

3. extract_exec_path

Encuentra la ruta de ejecución de un comando no interno.
Parámetros:
t_mshell_sack *sack: Estructura con el estado de la shell, incluyendo el entorno (envp).
t_cmd_node *node: Nodo del comando a ejecutar.
Funcionalidad:
Si el primer argumento del comando (args[0]) es un comando builtin, devuelve NULL (no se necesita buscar una ruta para los builtins).
Si el comando es una ruta (relativa o absoluta), verifica si el archivo existe con access(). Si existe, devuelve una copia de la ruta.
Si el comando no es una ruta y no existe la variable de entorno PATH, devuelve NULL.
Divide el PATH del entorno en directorios y prueba cada directorio concatenando el nombre del comando. Verifica si el comando existe en ese directorio con access(). Si lo encuentra, devuelve la ruta completa.
Si no encuentra el comando en ningún directorio del PATH, devuelve NULL.
Uso: Buscar la ruta correcta de un comando si no es un comando interno (builtin) y no se proporcionó como una ruta absoluta o relativa.


*/

#include "minishell.h"