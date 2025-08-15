/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:50:47 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/08 17:10:47 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <ctype.h>
# include <string.h>
# include <stddef.h>
# include <strings.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*Memory functions*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num, size_t size);

/*String functions*/
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/*Checker functions*/
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(unsigned char c);
int		ft_isalnum(char c);

/*Writing functions*/
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*Various functions*/
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);

/*Bonus list functions*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*get next line*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

/*get next line utils*/
char	*ft_free_join(char *stash, char *buffer);

/*get next line helpers*/
char	*ft_read_file(int fd, char *res);
char	*ft_line(char *stash);
char	*ft_update(char *stash);
void	get_next_line_clear(void);

#endif