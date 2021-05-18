/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:34:59 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/04 22:07:52 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen(const char *str)
{
	int		cnt;

	if (!str)
		return (0);
	cnt = 0;
	while (str[cnt] != '\0')
		cnt++;
	return (cnt);
}
