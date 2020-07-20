/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:24:25 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/07 19:44:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"


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

size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	if (!str)
		return (0);
	cnt = 0;
	while (str[cnt] != '\0')
		cnt++;
	return (cnt);
}


void	*ft_calloc(size_t size, size_t count)
{
	void		*addr;

	if (!(addr = malloc(size * count)))
		return (0);
	ft_memset(addr, 0, size * count);
	return (addr);
}

static char		*str_add(char *dst, char *src)
{
	int		i;
	int		j;

	if (!src)
		return (dst);
	if (!dst)
		return (src);
	i = ft_strlen(dst);
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	return (str);
}


char	*ft_strjoin(char *s1, char *s2, char *s3, char *s4)
{
	char	*str;
	int		lens;
	int		i;
	int		j;

	lens = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4);
	if (!(str = (char *)ft_calloc(sizeof(char), lens + 1)))
		return (0);
	str_add(str, s1);
	str_add(str, s2);
	str_add(str, s3);
	str_add(str, s4);
	return ((char *)str);
}
