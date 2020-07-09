/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isright_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:40:52 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/09 17:04:06 by eunhkim          ###   ########.fr       */
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
