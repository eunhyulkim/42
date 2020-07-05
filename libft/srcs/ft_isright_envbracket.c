/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isright_envbracket.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:40:52 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/05 14:52:01 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_quote(int *quote, char c)
{
	if (!(*quote))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

int			ft_isright_envbracket(char *src)
{
	int		idx;
	int		quote;

	idx = -1;
	quote = 0;
	while (src[++idx])
	{
		if (ft_isset(src[idx], "\'\""))
			handle_quote(&quote, src[idx]);
		if (!(src[idx] == '$' && src[idx + 1] == '{' && quote != '\''))
			continue;
		idx += 2;
		while (src[idx] && !ft_isset(src[idx], "{}\'\""))
			idx++;
		if (!src[idx] || src[idx] != '}')
			return (0);
	}
	return (1);
}
