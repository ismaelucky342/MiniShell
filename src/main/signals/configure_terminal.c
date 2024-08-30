#include "minishell.h"

void ft_configure_terminal(void)
{
    struct termios new_term;

    // Obtiene los atributos actuales del terminal asociado con STDIN (entrada estándar).
    tcgetattr(STDIN_FILENO, &new_term);

    // Desactiva la visualización de los caracteres de control (ECHOCTL).
    new_term.c_lflag &= ~(ECHOCTL);

    // Desactiva la señal asociada con la tecla de salida (QUIT), deshabilitando esta tecla.
    new_term.c_cc[VQUIT] = _POSIX_VDISABLE;

    // Establece los nuevos atributos del terminal.
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}
