LIB_SRC =	checkD_bf.c \
		free_2d.c \
		ft_addFS.c \
		ft_add_element.c \
		ft_arraylen.c \
		ft_atoi.c \
		ft_atoll.c \
		ft_bin2ascii.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_ch_value.c \
		ft_char.c \
		ft_char2bin.c \
		ft_create_element.c \
		ft_create_hashtable.c \
		ft_delete_element.c \
		ft_free_hashtable.c \
		ft_get_value.c \
		ft_hexadecimals.c \
		ft_index.c \
		ft_is_prime.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_ishexdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_monkey_hash.c \
		ft_next_prime.c \
		ft_number.c \
		ft_pointers.c \
		ft_print_hashtable.c \
		ft_printf.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_sqrt.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_string.c \
		ft_string2bin.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_unsigned.c \
		ins_sort.c \
		ft_del_list_np.c \
		ft_new_node.c \
		ft_add_node_end_np.c \
		ft_add_node_f_nextto_np.c  \
		ft_add_node_f_prevto_np.c  \
		ft_add_node_nextto_np.c \
		ft_add_node_prevto_np.c \
		ft_add_node_start_np.c \
		ft_del_node_end_np.c \
		ft_del_node_np.c \
		ft_del_node_start_np.c \
		ft_foreach_node_f_np.c \
		ft_swap_node_np.c \
		ft_printf_fd.c \
		ft_printf_fd_utils.c \
		ft_strnlen.c \
		skip_atoi.c \
		to_c.c \
		to_s.c \
		to_nbr.c \
		to_nbr_utils.c \
		to_n.c \
		get_next_line.c \
		get_next_line_utils.c \
		get_next_line_bonus.c \
		ft_strncpy.c 	\
		ft_strsub.c \
		ft_strcmp.c	\
		ft_print_error.c \
		ft_skip_spaces.c \
		ft_strcpy.c \
		ft_strjoin_free.c \
		ft_is_reserved_char.c \
		ft_strndup.c

G = \033[1;32m
R = \033[0;31m
NC = \033[0m

NAME = libft.a

LIB_OBJ_DIR = objects

LIB_OBJ = $(patsubst %.c, $(LIB_OBJ_DIR)/%.o, $(LIB_SRC))

CC = cc

all: $(NAME)
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)------------------------------------------ Libft Is Ready ------------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------\n$(NC)"

$(NAME): $(LIB_OBJ) libft.h
	ar -rcs $(NAME) $(LIB_OBJ)
	@echo "$(G)------------------------------------ Libft.a Finished Compiling ------------------------------------$(NC)\n"

$(LIB_OBJ_DIR):
	@mkdir -p $(LIB_OBJ_DIR)

$(LIB_OBJ_DIR)/%.o: %.c | $(LIB_OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf "%-200s\r" ">Libft compiling: ""$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<"

clean:
	@rm -rf $(LIB_OBJ_DIR)
	@echo "$(R)-------------------------------------- Libft Has Been Cleaned --------------------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
