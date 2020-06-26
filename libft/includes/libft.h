/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 01:06:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 18:51:48 by eunhkim          ###   ########.fr       */
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
int								ft_len_doublestr(char **arr);
char							**ft_dup_doublestr(char **arr);
char							*ft_strnstr(const char *s1, const char *s2, size_t len);

#endif
