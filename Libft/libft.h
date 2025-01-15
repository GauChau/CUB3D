/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:13:37 by julessainth       #+#    #+#             */
/*   Updated: 2024/12/11 15:58:51 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_mltsplit
{
	int		ix;
	char	*s;
	int		mltsplit_l;
}				t_mltsplit;

void		*ft_memdel(void *ptr);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *d, const void *s, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *s);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *d, const char *s, size_t dstsize);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*get_next_line(int fd);
char		*ft_strchr(const char *string, int searchedChar );
long		ft_atoi_l(const char *str);
char		*ft_splitcat(char **ft_split);
char		**ft_split_ignoreQuote(char const *s, char c);
int			ft_last_strchr_i(const char *string, char a, char b);
char		*ft_strjoin_free(char *s1, char *s2);
void		ft_putquote(char *s, int fd);
char		*ft_str_remvchr(char *s, char a, char b);
int			ft_str_isalpha(char *s);
char		ft_inq(char q, char si);
int			ft_char_in_set(char c, char *set);
void		ft_free_multisplit(t_mltsplit *s);
void		ft_free_split(char **s);
void		ft_free_tab(char **tab);
int			ft_stronly(char *s, char c);
int			ft_str_isalnum(char *s);

/* additional functions */
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
int			ft_m_strchr_i(const char *string, char a, char b);
void		ft_putendl(char *s);

/* bonus */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

char		*ft_rm_quotes(char *s);
void		ft_apply_rmquote(char **t);
t_mltsplit	*ft_multisplit(char *s, char *set);
char		**ft_split_quotes(char *s, char c, int remove_quote);

/* gnl */
char		*get_next_line(int fd);
int			gnl_strlen(char *dst, char *src, int siz, int alt);

#endif
