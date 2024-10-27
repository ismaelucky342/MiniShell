G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m

PIPEX_NAME		=	$(PIPEX_OBJ_DIR)/pipex_main
PIPEX_B_NAME	=	$(PIPEX_OBJ_DIR)/pipex_bonus
PIPEX_OUTPUT	=	pipex

PIPEX_SRC		=	main.c \
					forker.c \
					executioner.c \

PIPEX_B_SRC		=	main_bonus.c \
					executioner.c \
					forker.c \

PIPEX_OBJ_DIR	=	objects

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -g3 #-fsanitize=address

LIBFT			=	./Libft/libft.a

PIPEX_INCLUDE	=	pipex.h

PIPEX_OBJ		=	$(patsubst %.c, $(PIPEX_OBJ_DIR)/%.o, $(PIPEX_SRC))

all: $(PIPEX_NAME)
	@cp $(PIPEX_NAME) $(PIPEX_OUTPUT)
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)------------------------------------------ Pipex Is Ready ------------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"

$(PIPEX_NAME): $(LIBFT) $(PIPEX_OBJ) $(PIPEX_INCLUDE)
	@$(CC) $(CFLAGS) $(PIPEX_OBJ) $(LIBFT) -o $(PIPEX_NAME)
	@printf "%-109s\r" "                                                                                                             "
	@echo "$(G)------------------------------------- Pipex Finished Compiling -------------------------------------$(NC)\n"

$(PIPEX_OBJ_DIR):
	@mkdir -p $(PIPEX_OBJ_DIR)

bonus:
	@make -s PIPEX_NAME="$(PIPEX_B_NAME)" PIPEX_SRC="$(PIPEX_B_SRC)"
	@echo "$(G)\n----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)------------------------------------------ Bonus Included ------------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"

$(LIBFT):
	@make -sC ./Libft bonus

$(PIPEX_OBJ_DIR)/%.o: %.c | $(PIPEX_OBJ_DIR) $(PIPEX_INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "%-109s\r" ">Pipex compiling: ""$(CC) $(CFLAGS) -c -o $@ $<"

clean:
	@make -sC ./Libft fclean
	@rm -rf $(PIPEX_OBJ_DIR)
	@echo "$(R)-------------------------------------- Pipex Has Been Cleaned --------------------------------------$(NC)"

fclean: clean
	@rm -f $(PIPEX_NAME) $(PIPEX_B_NAME) pipex

re: fclean all

reb: fclean bonus

.PHONY: all clean fclean re reb bonus
