/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isformat2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:04:48 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/09 17:04:50 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		check_char(char **str, char *format)
{
	if (!(*str) || !(*(*str)) || *(*str) != *format)
		return (0);
	*str = *str + 1;
	return (1);
}

static int		check_wild(char **str, char *format, int *main_idx)
{
	int		idx;
	int		valid;

	idx = 0;
	valid = 0;
	while (format[idx] && format[idx] == '*')
		idx++;
	if (!format[idx])
	{
		while (*(*str))
			*str = *str + 1;
		return (1);
	}
	while (*(*str) && *(*str) != format[idx])
		*str = *str + 1;
	if (!(*(*str)))
		return (0);
	valid = ft_isformat2(*str, &format[idx]);
	if (!valid && (valid = ft_isformat2(*str + 1, &format[idx - 1])))
	{
		*str = *str + 1;
		*main_idx = idx - 2;
	}
	return (valid);
}

int				ft_isformat2(char *str, char *format)
{
	int			idx;
	int			valid;

	if (!str || !format)
		return (0);
	if (*format && *format != '*' && !(*str))
		return (0);
	idx = 0;
	valid = 1;
	while (format[idx] && valid)
	{
		if (format[idx] != '*')
			valid = check_char(&str, &format[idx]);
		else if (format[idx] == '*')
			valid = check_wild(&str, &format[idx], &idx);
		idx++;
	}
	return ((!(*str) && !(format[idx]) && valid) ? 1 : 0);
}
