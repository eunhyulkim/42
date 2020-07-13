/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isright_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:22:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 12:22:59 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isright_quote(char *src)
{
	int		idx;
	int		quote;

	idx = 0;
	quote = 0;
	while (src[idx])
	{
		if (ft_isset(src[idx], "\'\""))
		{
			if (!quote)
				quote = src[idx];
			else if (quote == src[idx])
				quote = 0;
		}
		idx++;
	}
	return (quote == 0);
}
