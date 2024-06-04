GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

SRC =	ft_substr.c ft_isalpha.c ft_memcpy.c \
		ft_strlcpy.c ft_toupper.c ft_isascii.c \
		ft_memmove.c ft_strlen.c ft_atoi.c \
		ft_isdigit.c ft_memset.c ft_strncmp.c \
		ft_bzero.c ft_isprint.c ft_strchr.c \
		ft_strnstr.c ft_calloc.c ft_memchr.c \
		ft_strdup.c ft_strrchr.c ft_isalnum.c \
		ft_memcmp.c ft_strlcat.c ft_tolower.c \
		ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_sqrt.c \

B_SRC =	ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \

NAME = libft.a

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize="address"

all: $(NAME) libft.h
	@echo "$(GREEN)----------------------------------------------------------------$(NC)"
	@echo "$(GREEN)------------------------ Libft Is Ready ------------------------$(NC)"
	@echo "$(GREEN)----------------------------------------------------------------$(NC)\n"

$(NAME): $(OBJ) 
	@ar -rcs $(NAME) $(OBJ)
	@echo "$(GREEN)------------------ Libft.a Finished Compiling ------------------$(NC)\n"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

bonus:
	@echo "$(YELLOW)------------------ Compiling Libft And Bonus -------------------$(NC)"
	@make -s SRC='$(SRC) $(B_SRC)'

clean:
	@rm -f $(OBJ) $(B_OBJ)
	@echo "$(RED)------------------------ Libft Cleaned -------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
