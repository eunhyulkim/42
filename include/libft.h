/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 01:06:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 01:46:33 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned char			t_uchar;
typedef unsigned int			t_uint;
typedef unsigned long int		t_ulint;
typedef unsigned long long int	t_ullint;
typedef long double				t_ldouble;
typedef long long int			t_llint;

typedef struct					s_list
{
	void						*content;
	struct s_list				*next;
}								t_list;

/*
** math
*/
// t_llint							ft_abs(t_llint num);
// char							*ft_convert_base(char *nbr, char *base_from, \
// 								char *base_to);
// int								ft_digit(t_llint num);
// int								ft_nbrsize(int *nbr);
// int								ft_nextprime(int nbr);
// t_llint							ft_pow(t_llint num, int pow);
// t_ldouble						ft_round(t_ldouble n, int digit);
// int								ft_sqrt(int nb);
// int								ft_swapi(int *nb1, int *nb2);

/*
** string
*/
// t_llint							ft_atoll(char *str);
// t_llint							ft_moveatoll(char **straddr);
// char							*ft_etoa(t_ldouble n, t_uint len, t_uint gopt);
// char							*ft_ftoa(t_ldouble n, t_uint len);
// char							*ft_lltoa(t_llint n);
// char							*ft_ultoa(t_ullint n);
// char							*ft_lftovna(t_ldouble n, int len);
// void							ft_putchar_fd(char c, int fd);
// void							ft_putendl_fd(char *s, int fd);
// void							ft_putnbr_fd(t_llint n, int fd);
// void							ft_putstr_fd(char *s, int fd);
// char							**ft_split(char const *s, char c);
char							*ft_strchr(const char *s, int c);
// char							*ft_strrchr(const char *s, int c);
// char							*ft_strnstr(const char *s1, const char *s2, \
// 								size_t len);
// char							*ft_substr(char const *s, t_uint start, \
// 								size_t len);
// char							*ft_strdup(const char *src);
// char							*ft_strfreedup(char *remove, char *src);
// char							*ft_strinsert(char *dest, char *str, \
// 								char *src);
// t_uchar							*ft_strjoin(char const *s1, char const *s2);
// char							*ft_strmjoin(char *s1, char *s2);
// char							*ft_strremove(char *dest, char *str, int opt);
// size_t							ft_strlcat(char *dest, const char *src, \
// 								size_t size);
// size_t							ft_strlcpy(char *dest, const char *src, \
// 								size_t size);
size_t							ft_strlen(const char *str);
// char							*ft_strmapi(char const *s, \
// 								char (*f)(t_uint, char));
// int								ft_strncmp(const char *s1, const char *s2, \
// 								size_t n);
// int								ft_strssize(char **strs);
// char							*ft_strtrim(char const *s1, char const *set);
// int								ft_swapc(char *s1, char *s2);
// int								ft_toupper(int c);
// int								ft_tolower(int c);
// char							*ft_trans_base(t_ullint nb, char *base);
// t_uchar							*ft_ustrdup(const t_uchar *src);
// size_t							ft_ustrlen(const t_uchar *str);
// t_uchar							*ft_ustrmjoin(t_uchar *s1, t_uchar *s2);
// t_uchar							*ft_ustrremove(t_uchar *dest, t_uchar *str);

/*
** is
*/
// int								ft_isalnum(int c);
// int								ft_isalpha(int c);
// int								ft_isascii(int c);
// int								ft_islower(int c);
// int								ft_isnum(long long c);
// int								ft_isprint(int c);
// int								ft_isset(int c, char *set);
// int								ft_isupper(int c);
// int								ft_iszero(char *str);
// int								ft_isformat(char *str, char *format);
// int								ft_isspace(int c);

/*
** bit
*/
// void							ft_bzero(void *data, size_t len);
// void							*ft_memcpy(void *dst, const void *src, \
// 								size_t n);
// void							*ft_memmove(void *dst, const void *src, \
// 								size_t len);
// void							*ft_memset(void *data, int c, size_t len);
// void							*ft_memccpy(void *dst, const void *src, \
// 								int c, size_t n);
// void							*ft_memchr(const void *s, int c, size_t n);
// int								ft_memcmp(const void *s1, const void *s2, \
// 								size_t n);

/*
** memory
*/
// void							*ft_calloc(size_t count, size_t size);
// void							ft_memset_int_two(int *n1, int *n2, int v);
// void							ft_memset_int_three(int *n1, int *n2, \
// 								int *n3, int v);
// void							ft_memset_int_four(int *n1, int *n2, \
// 								int *n3, int *n4);

/*
** lst
*/
// void							ft_lstadd_back(t_list **lst, t_list *new);
// void							ft_lstadd_front(t_list **lst, t_list *new);
// void							ft_lstclear(t_list **lst, void (*del)(void *));
// void							ft_lstdelone(t_list *lst, void (*del)(void *));
// void							ft_lstiter(t_list *lst, void (*f)(void *));
// t_list							*ft_lstlast(t_list *lst);
// t_list							*ft_lstmap(t_list *lst, void *(*f)(void *), \
// 								void (*del)(void *));
// t_list							*ft_lstnew_strs(int size, char **strs, \
// 								int sort);
// t_list							*ft_lstnew(void *content);
// int								ft_lstsize(t_list *lst);
#endif
