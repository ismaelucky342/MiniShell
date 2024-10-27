G = \033[1;32m
R = \033[0;31m
NC = \033[0m

LIB_SRC =	ft_substr.c ft_isalpha.c ft_memcpy.c \
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

LIB_B_SRC =	ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \

NAME = libft.a

LIB_OBJ_DIR = objects

LIB_OBJ = $(patsubst %.c, $(LIB_OBJ_DIR)/%.o, $(LIB_SRC))

CC = gcc

LIB_INCLUDE = libft.h

CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)------------------------------------------ Libft Is Ready ------------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"

bonus:
	@make -s LIB_SRC="$(LIB_SRC) $(LIB_B_SRC)"
	@echo "$(G)\n----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)------------------------------------------ Bonus Included ------------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"

$(NAME): $(LIB_OBJ) libft.h
	@ar -rcs $(NAME) $(LIB_OBJ)
	@echo "$(G)------------------------------------ Libft.a Finished Compiling ------------------------------------$(NC)\n"

$(LIB_OBJ_DIR):
	@mkdir -p $(LIB_OBJ_DIR)

$(LIB_OBJ_DIR)/%.o: %.c | $(LIB_OBJ_DIR) $(LIB_INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "%-109s\r" ">Libft compiling: ""$(CC) $(CFLAGS) -c -o $@ $<"

clean:
	@rm -rf $(LIB_OBJ_DIR)
	@echo "$(R)-------------------------------------- Libft Has Been Cleaned --------------------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

reb: fclean bonus

.PHONY: all clean fclean re bonus reb
