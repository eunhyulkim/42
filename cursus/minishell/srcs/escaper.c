/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:24:34 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 22:22:50 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handle_quote(char *quote, char quote_char)
{
	if (!(*quote))
		*quote = quote_char;
	else if (*quote && *quote == quote_char)
		*quote = 0;
	return ;
}

static void		no_quote_escape(char **line, char *old_line, int *i)
{
	if (!(old_line[*i + 1]))
		return ;
	ft_realloc(line, old_line[*i + 1] * -1);
	*i += 1;
}

static void		double_quote_escape(char **line, char *old_line, int *i)
{
	if (old_line[*i + 1] == '\n' && !old_line[*i + 2])
		return ;
	if (!(ft_isset(old_line[*i + 1], "\\$`\"\n")))
	{
		ft_realloc(line, old_line[*i]);
		return ;
	}
	ft_realloc(line, old_line[*i + 1] * -1);
	*i += 1;
}

char			*escaper(char *old_line)
{
	char	*line;
	int		i;
	char	quote;

	line = 0;
	quote = 0;
	i = 0;
	while (old_line[i])
	{
		if (!quote && old_line[i] == '\\')
			no_quote_escape(&line, old_line, &i);
		else if (quote == '\"' && old_line[i] == '\\')
			double_quote_escape(&line, old_line, &i);
		else
		{
			if (ft_isset(old_line[i], "\'\""))
				handle_quote(&quote, old_line[i]);
			ft_realloc(&line, old_line[i]);
		}
		i++;
	}
	ft_free_str(&old_line);
	return (line);
}
