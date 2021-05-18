/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_doublestr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:29:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 20:07:07 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_doublestr(char **str)
{
	char	**ret;
	int		len;

	len = ft_len_doublestr(str);
	if (!(ret = (char **)ft_calloc(sizeof(char *), len + 1)))
		return (0);
	while (len--)
		if (!(ret[len] = ft_strdup(str[len])))
			return (0);
	return (ret);
}
