/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:31:16 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:48:50 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*str;

	if (!s || !f)
		return (0);
	len = (ft_strlen(s));
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	str[len] = 0;
	i = -1;
	while (++i < len)
		str[i] = f((t_uint)i, s[i]);
	return (str);
}
