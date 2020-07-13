/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:24:34 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 12:24:35 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void 	handle_quote(char *quote, char quote_char)
{
	if (!(*quote))
		*quote = quote_char;
	else if (*quote && *quote == quote_char)
		*quote = 0;
	return ;
}

char 			*escaper(char *old_line)
{
	char 	*line;
	int		i;
	char	quote;

	line = 0;
	quote = 0;
	i = 0;
	while (old_line[i])
	{
		if (quote != '\'' && old_line[i] == '\\')
		{
			if (old_line[i + 1])
				ft_realloc(&line, old_line[++i] * -1);
		}
		else
		{
			if (ft_isset(old_line[i], "\'\""))
				handle_quote(&quote, old_line[i]);
			ft_realloc(&line, old_line[i]);
		}
		i++;
	}
	free(old_line);
	return (line);
}
