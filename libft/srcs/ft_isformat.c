/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isformat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:13:57 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 22:13:59 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_right(char **str, char **format)
{
	int			n;

	n = 1;
	while ((*format)[n] && (*format)[n] != ']')
		n++;
	if (!((*format)[n]))
		return (0);
	n = n - 1;
	if (ft_strncmp(*str, (*format + 1), n) != 0)
	{
		if (*(*format + n + 2) == '?')
		{
			*format = *format + n + 3;
			return (1);
		}
		else
			return (0);
	}
	*format += (*(*format + n + 2) == '?') ? n + 3 : n + 2;
	*str = *str + n;
	return (1);
}

static int		check_char(char **str, char **format)
{
	char		c;

	c = *(*format);
	if (c == ' ' && !ft_isspace(*(*str)))
		return (0);
	if (c == 'c' && !ft_isalpha(*(*str)))
		return (0);
	if (c == 'd' && !ft_isnum(*(*str)))
		return (0);
	if (c == '*' && !ft_isprint(*(*str)))
		return (0);
	if (c == '*' && ft_isspace(*(*str)))
		return (0);
	*str = *str + 1;
	*format = *format + 1;
	return (1);
}

static int		check_string(char **str, char **format)
{
	if (!check_char(str, format))
		return (0);
	*format = *format - 1;
	while (check_char(str, format))
		*format = *format - 1;
	*format = *format + 1;
	while (ft_isset(*(*format), "?+"))
		*format = *format + 1;
	return (1);
}

static void		handling_others(char **str, char **format)
{
	char		c;
	char		duple;

	c = *(*format);
	duple = 0;
	if (!check_char(str, format))
		*format = *format + 1;
	if (*(*format) == '+')
		duple = 1;
	if (*(*format) == '?' && *(*format + 1) == '+')
		duple = 1;
	while (duple && c == ' ' && ft_isspace(*(*str)))
		*str = *str + 1;
	while (duple && c == 'c' && ft_isalpha(*(*str)))
		*str = *str + 1;
	while (duple && c == 'd' && ft_isnum(*(*str)))
		*str = *str + 1;
	while (duple && c == '*' && ft_isprint(*(*str)) && !ft_isspace(*(*str)))
		*str = *str + 1;
	while (ft_isset(*(*format), "?+"))
		*format = *format + 1;
}

int				ft_isformat(char *str, char *format)
{
	int			valid;

	valid = 1;
	while (*format && valid)
	{
		if (!ft_isset(*format, "[cd* "))
			return (0);
		if (*format == '[')
			valid = check_right(&str, &format);
		else if (!ft_isset(*(format + 1), "?+"))
			valid = check_char(&str, &format);
		else if (*(format + 1) == '+' && *(format + 2) != '?')
			valid = check_string(&str, &format);
		else
			handling_others(&str, &format);
	}
	return ((!(*str) && !(*format) && valid) ? 1 : 0);
}
