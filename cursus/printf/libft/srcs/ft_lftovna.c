/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lftovna.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:12:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/10 16:15:25 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_lftovna(t_ldouble n, int len)
{
	int			cnt;
	t_llint		nb;
	char		*str;

	if (n == (t_ldouble)(nb = 0))
		return (ft_strdup("0"));
	if ((cnt = (len - ft_digit((t_llint)n))) <= 0)
		return (ft_lltoa((nb = n) / ft_pow(10, ft_abs(cnt))));
	if (ft_digit(nb = n) >= 1)
		str = ft_ftoa(n, cnt);
	else
	{
		cnt = 0;
		while ((nb = n * ft_pow(10, cnt + 1)) % 10 == 0)
			cnt++;
		str = ft_ftoa(n, cnt + len);
	}
	cnt = ft_strlen(str) - 1;
	while (cnt >= 0 && str[cnt] == '0')
		cnt--;
	if (cnt >= 1 && str[cnt] == '.')
		cnt--;
	if ((size_t)++cnt != ft_strlen(str))
		str = ft_strremove(str, &str[cnt], 0);
	return (str);
}
