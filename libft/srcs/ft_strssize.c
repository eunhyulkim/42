/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strssize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:34:59 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/08 01:57:58 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strssize(char **strs)
{
	int		cnt;

	if (!strs || !(*strs))
		return (0);
	cnt = 0;
	while (strs[cnt] != '\0')
		cnt++;
	return (cnt);
}
