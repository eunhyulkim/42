/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 22:14:55 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:53:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *data, size_t len)
{
	t_uchar	*str;

	str = (t_uchar *)data;
	while (len > 0)
		str[--len] = 0;
}
