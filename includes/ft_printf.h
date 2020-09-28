/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 01:29:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/09/24 15:15:31 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include <ctype.h>
# include <assert.h>
# include <unistd.h>
# include <stdlib.h>
# include <locale.h>

typedef unsigned char			t_uchar;
typedef unsigned int			t_uint;
typedef unsigned short int		t_usint;
typedef unsigned long int		t_ulint;
typedef unsigned long long int	t_ullint;
typedef short int				t_sint;
typedef long int				t_lint;
typedef long long int			t_llint;
typedef long double				t_ldouble;

typedef struct					s_tab
{
	char						*origin;
	char						*treat;
	char						flag[5];
	void						*content;
	t_uint						width;
	t_uint						sharp[2];
	t_uint						size;
	t_uint						type;
	t_uint						count;
	t_uint						length;
	t_uchar						*w_size;
	va_list						ap;
}								t_tab;


/*
** main
*/
int								ft_printf(const char *format, ...);
void							action(t_tab *tab);
int								arrange(t_tab *tab);

/*
** parsing
*/
void							put_flag(char c, t_tab *tab);
int								has_flag(char c, t_tab *tab);
void							unuse_flag(char *set, t_tab *tab);
void							check_flag(t_tab *tab);
void							check_width(t_tab *tab);
int								get_sharp(t_tab *tab);
int								has_sharp(t_tab *tab);
void							check_sharp(t_tab *tab);
void							check_size(t_tab *tab);
int								check_type(t_tab *tab);

/*
** conversion
*/
void							deliver(t_tab *tab);
t_llint							conv_arg_ll(t_tab *tab);
t_ullint						conv_arg_ull(t_tab *tab);
void							conversion_c(t_tab *tab);
void							conversion_s(t_tab *tab);
void							conversion_p(t_tab *tab);
void							conversion_di(t_tab *tab);
void							conversion_u(t_tab *tab);
void							conversion_xx(t_tab *tab);
void							conversion_o(t_tab *tab);
void							conversion_oo(t_tab *tab);
void							conversion_n(t_tab *tab);
void							conversion_f(t_tab *tab);
void							conversion_g(t_tab *tab);
void							conversion_e(t_tab *tab);
void							conversion_wc(t_tab *tab);
void							conversion_ws(t_tab *tab);

/*
** print
*/
void							print_content(t_tab *tab);
void							reinitialize(t_tab *tab);
#endif
