/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 01:06:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/30 11:47:54 by eunhkim          ###   ########.fr       */
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

char							*ft_strchr(const char *s, int c);
int								ft_strlen(const char *str);
char							**ft_split(char const *s, char c);
char							*ft_strdup(const char *src);
void							*ft_memset(void *data, int c, size_t len);
void							*ft_calloc(size_t size, size_t count);
char							*ft_strnstr(const char *s1, const char *s2, size_t len);
char							*ft_strcpy(char *dest, const char *src);
char							*ft_strcat(char *dest, const char *src);
char							*ft_strjoin(char const *s1, char const *s2);
char							*ft_strsub(char const *s, unsigned int start, size_t len);
int								ft_strcmp(const char *s1, const char *s2);
int								ft_strncmp(const char *s1, const char *s2, size_t n);
void							ft_putstr_fd(char *str, int fd);
int								ft_isspace(int c);
int								ft_isascii(int c);
int								ft_isalpha(int c);
int								ft_isnum(t_llint c);
int								ft_isprint(int c);
int								ft_isset(int c, char *set);

// bonus
int								ft_len_doublestr(char **arr);
char							**ft_dup_doublestr(char **arr);
int								ft_free_doublestr(char **double_arr);
char							**ft_realloc_doublestr(char ***strs_ref, char *item);
int								ft_startswith(const char *str, const char *sub);
char							*ft_strnew(size_t size);
int								ft_in(char *item, char *list);
int								ft_isitem(char *item, char **list);
int								ft_isformat(char *str, char *format);
char							*ft_strreverse(char *src);
int								ft_free(char *str);

#endif
