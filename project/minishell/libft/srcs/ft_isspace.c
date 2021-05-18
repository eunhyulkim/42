/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 02:58:52 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/08 00:39:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isspace(int c)
{
	if (c == '\t' || c == '\r' || \
	c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}
