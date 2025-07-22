/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:44:22 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/22 14:22:08 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Libft bonus
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *list, void *(*f)(void *), void (*del)(void *));

// Libft de base
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
size_t	ft_strlen(const char *str);
int		ft_isprint(int c);
void	*ft_memset(void *b, int c, size_t len);
int		ft_atoi(const char *str);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t len_dest);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *str, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_striteri(char *str, void (*f)(unsigned int, char *));
char	*ft_strdup(const char *src);
char	**ft_split(char const *str, char c);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_itoa(int n);

// Printf
int		ft_printf(const char *format, ...);
int		ft_conv(char c, va_list args);
int		ft_putpercent(void);
int		ft_putptr(void *ptr);
int		ft_puthex(char c, unsigned long n);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putnbr(int n);
int		ft_putstr(char *str);
int		ft_putchar(char c);

// get_next_line
char	*ft_get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strfreejoin(char *s1, char *s2);

// rajouté par moi
int		ft_count_num(int n);
int		ft_count_word(char const *str, char c);
void	ft_free_tab(char **tab);
int		ft_sort_int_tab(int *tab, int size);
size_t	ft_strcspn(const char *str, const char *reject);
int		ft_strcmp(const char *s1, const char *s2);

#endif
