/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/07/21 13:27:59 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef int			t_bool;
# define TRUE 1
# define FALSE 0

/*STRUCT HASH */
typedef struct s_element
{
	char			*key;
	char			*value;
}					t_element;

typedef struct s_hashtable
{
	t_element		**element_array;
	int				length;
}					t_hashtable;

// new functions
void				ft_bin2ascii(char *s);
char				*ft_string2bin(char *s, size_t i, size_t j);
void				ft_char2bin(unsigned char c, char *ret, size_t *j);
char				*ft_add_fs(char *start, char c);
int					ft_ishexdigit(int c);
int					ft_isspace(int c);
void				display_error(char *error_msg, t_bool yeet);
void				free_2d(char **arr);
int64_t				ft_atoll(const char *str);
int					ft_sqrt(int number);
int					checkd_bf(int *numbers, int count);
void				ins_sort(int array[], int n);

// printf
int					ft_print_char(int character);
int					ft_printf(const char *str, ...);
int					ft_print_str(char *str);
int					ft_print_number(int n);
int					ft_print_unsigned(unsigned int n);
int					ft_print_hex(unsigned int num, const char word);
int					ft_print_pointer(unsigned long long ptr);

// libft
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *dst, const void *str, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **list, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *list, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/*HASH FUNCTIONS*/
t_hashtable			*ft_add_element(t_hashtable *ht, char *key, char *value);
t_element			*ft_get_element(t_hashtable *ht, char *key);
t_hashtable			*ft_ch_value(t_hashtable *ht, char *key, char *value, int is_apnd);
t_element			*ft_create_element(char *key, char *value);
t_hashtable			*ft_create_hashtable(int length);
t_hashtable			*ft_delete_element(t_hashtable *ht, char *key);
void				ft_free_hashtable(t_hashtable *hashtable);
void				ft_free_element(t_element *element);
char				*ft_get_value(t_hashtable *hashtable, char *key);
int					ft_monkey_hash(char *str, int length);
void				ft_print_hashtable(t_hashtable *hashtable, char *delimeter);
int					ft_arraylen(char **str);
int					ft_next_prime(int nbr);
int					ft_index(char *str, char c);
int					ft_is_prime(int nbr);

#endif
