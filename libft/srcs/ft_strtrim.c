/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:31:41 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:14:31 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const s1, char const *set)
{
	int		i;

	if (set == 0 || *set == 0)
		return (0);
	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		last;
	int		i;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && is_set(s1[i], set))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (is_set(s1[i], set))
		i--;
	last = i;
	if (last < start)
		last = start - 1;
	if (!(str = (char *)malloc(sizeof(char) * (last - start + 2))))
		return (0);
	i = 0;
	while (start <= last)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
