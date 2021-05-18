/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:06:16 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 17:27:01 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static t_ullint		make_magic(t_ullint **l_addr, t_uchar *c_addr, int c)
{
	t_ullint		magic;

	magic = 0xff & c;
	magic = (magic << 8) | magic;
	magic = (magic << 16) | magic;
	magic = ((magic << 16) << 16) | magic;
	*l_addr = (t_ullint *)c_addr;
	return (magic);
}

void				*ft_memset(void *data, int c, size_t len)
{
	t_ullint		magic;
	t_ullint		*l_addr;
	t_uchar			*c_addr;

	l_addr = NULL;
	c_addr = (t_uchar *)data;
	while (((t_ullint)c_addr & (sizeof(magic) - 1)) && len)
	{
		*c_addr++ = c;
		--len;
	}
	if (len >= 8)
	{
		magic = make_magic(&l_addr, (void *)c_addr, c);
		while (len >= 8)
		{
			*l_addr++ = magic;
			len -= 8;
		}
	}
	c_addr = (l_addr == NULL) ? c_addr : (t_uchar *)l_addr;
	while (len--)
		*c_addr++ = c;
	return (data);
}

void				*ft_calloc(size_t size, size_t count)
{
	void		*addr;

	if (!(addr = malloc(size * count)))
		return (0);
	ft_memset(addr, 0, size * count);
	return (addr);
}

char				*ft_strmjoin(char *s1, char *s2)
{
	char	*str;
	int		lens;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	lens = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (lens + 1))))
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		str[i++] = s2[j];
	str[i] = 0;
	free(s1);
	free(s2);
	return (str);
}

char				*ft_itoa(t_llint n)
{
	t_llint		nb;
	int			digit;
	char		*str;

	nb = (n < 0) ? -n : n;
	digit = (n <= 0) ? 1 : 0;
	while (nb > 0)
	{
		nb /= 10;
		digit++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (digit + 1))))
		return (0);
	str[digit--] = 0;
	nb = (n < 0) ? -n : n;
	while (nb > 0)
	{
		str[digit] = (nb % 10) + 48;
		nb = nb / 10;
		digit--;
	}
	str[0] = (n < 0) ? '-' : str[0];
	str[0] = (n == 0) ? '0' : str[0];
	return (str);
}
