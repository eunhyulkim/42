/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:06:16 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:06:17 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
