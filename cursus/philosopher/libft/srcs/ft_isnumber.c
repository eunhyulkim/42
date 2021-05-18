/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 20:26:01 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 20:28:47 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isnumber(char *str)
{
	if (!str || !(*str))
		return (0);
	while (*str && *str >= 48 && *str <= 57)
		str++;
	return (*str == '\0');
}