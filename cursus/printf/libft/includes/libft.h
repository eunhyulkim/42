/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 01:06:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:18:56 by eunhkim          ###   ########.fr       */
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

void							*ft_memset(void *data, int c, size_t len);
size_t							ft_strlen(const char *str);
int								ft_isnum(long long c);
int								ft_isset(int c, char *set);
int								ft_iszero(char *str);

void							ft_putchar_fd(char c, int fd);
void							ft_putnbr_fd(t_llint n, int fd);
void							ft_putstr_fd(char *s, int fd);

t_llint							ft_atoll(char *str);
t_llint							ft_moveatoll(char **straddr);
char							*ft_lltoa(t_llint n);
char							*ft_ultoa(t_ullint n);
char							*ft_etoa(t_ldouble n, t_uint len, t_uint gopt);
char							*ft_ftoa(t_ldouble n, t_uint len);
char							*ft_lftovna(t_ldouble n, int len);

char							*ft_strchr(const char *s, int c);
char							*ft_strrchr(const char *s, int c);
char							*ft_strnstr(const char *s1, const char *s2, \
								size_t len);

char							*ft_strdup(const char *src);
char							*ft_strfreedup(char *remove, char *src);
char							*ft_strinsert(char *dest, char *str, \
								char *src);
char							*ft_strremove(char *dest, char *str, int opt);
char							*ft_strmjoin(char *s1, char *s2);

t_llint							ft_abs(t_llint num);
int								ft_digit(t_llint num);
int								ft_swapc(char *s1, char *s2);
t_llint							ft_pow(t_llint num, int pow);
char							*ft_trans_base(t_ullint nb, char *base);

t_uchar							*ft_ustrmjoin(t_uchar *s1, t_uchar *s2);
size_t							ft_ustrlen(const t_uchar *str);
t_uchar							*ft_ustrdup(const t_uchar *src);
t_uchar							*ft_ustrremove(t_uchar *dest, t_uchar *str);
t_ldouble						ft_round(t_ldouble n, int digit);
#endif
