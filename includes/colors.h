#ifndef COLORS_H
# define COLORS_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>

/* COLORS */
# define COLOR_RESET "\033[0m"

# define COLOR_BACKGROUND_BLACK "\033[40m"
# define COLOR_BACKGROUND_RED "\033[41m"
# define COLOR_BACKGROUND_GREEN "\033[42m"
# define COLOR_BACKGROUND_YELLOW "\033[43m"
# define COLOR_BACKGROUND_BLUE "\033[44m"
# define COLOR_BACKGROUND_MAGENTA "\033[45m"
# define COLOR_BACKGROUND_CYAN "\033[46m"
# define COLOR_BACKGROUND_WHITE "\033[47m"
# define COLOR_BACKGROUND_GRAY "\033[100m"

# define COLOR_BLACK_TEXT "\033[30m"
# define COLOR_RED_TEXT "\033[31m"
# define COLOR_GREEN_TEXT "\033[32m"
# define COLOR_YELLOW_TEXT "\033[33m"
# define COLOR_BLUE_TEXT "\033[34m"
# define COLOR_MAGENTA_TEXT "\033[35m"
# define COLOR_CYAN_TEXT "\033[36m"
# define COLOR_WHITE_TEXT "\033[37m"
# define COLOR_GRAY_TEXT "\033[90m"

# define COLOR_BOLD_BLACK_TEXT "\033[30;01m"
# define COLOR_BOLD_RED_TEXT "\033[31;01m"
# define COLOR_BOLD_GREEN_TEXT "\033[32;01m"
# define COLOR_BOLD_YELLOW_TEXT "\033[33;01m"
# define COLOR_BOLD_BLUE_TEXT "\033[34;01m"
# define COLOR_BOLD_MAGENTA_TEXT "\033[35;01m"
# define COLOR_BOLD_CYAN_TEXT "\033[36;01m"
# define COLOR_BOLD_WHITE_TEXT "\033[37;01m"
# define COLOR_BOLD_GRAY_TEXT "\033[90;01m"

#endif