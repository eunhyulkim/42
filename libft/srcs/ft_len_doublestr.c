/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_doublestr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:29:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 18:24:27 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_len_doublestr(char **str)
{
	int		idx;

	idx = 0;
	if (!str)
		return (0);
	while (*str++)
		idx++;
	return (idx);
}
