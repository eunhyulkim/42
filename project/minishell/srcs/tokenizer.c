/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:45:07 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/12 23:31:29 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		tab_init(t_tokenizer *tool)
{
	tool->idx = 0;
	tool->qidx = 0;
	tool->start = -1;
	tool->prev = 0;
	tool->quote = FALSE;
}

static char		get_quote(char *line, int idx)
{
	char	quote;

	quote = 0;
	if (line[idx] == '\'')
		quote = '\'';
	else if (line[idx] == '\"')
		quote = '\"';
	return (quote);
}

static	int		is_start(char *line, t_tokenizer *tool)
{
	int		i;

	i = tool->idx;
	if (!line || !line[i] || tool->quote)
		return (FALSE);
	if ((tool->quote = get_quote(line, i)))
		tool->qidx = i;
	if (line[i] == '\n')
		return (TRUE);
	if (ft_isset(line[i], "><|;&"))
	{
		if (tool->prev == line[i])
			return (FALSE);
		tool->prev = line[i];
		return (TRUE);
	}
	tool->prev = 0;
	if (!tool->idx)
		return (TRUE);
	if (ft_isspace(line[i]))
		return (ft_isspace(line[i - 1]) ? FALSE : TRUE);
	return (ft_isspace(line[i - 1]) || ft_isset(line[i - 1], "><|;&"));
}

static	int		is_end(char *line, t_tokenizer *tool)
{
	int		i;

	i = tool->idx;
	if (!line || tool->start == -1)
		return (FALSE);
	if (line[i] == tool->quote && tool->qidx != i)
		tool->quote = FALSE;
	if (!line[i + 1] || (!tool->quote && line[i] == '\n'))
		return (TRUE);
	if (!tool->quote && line[i + 1] == '\n')
		return (TRUE);
	if (tool->quote)
		return (FALSE);
	if (ft_isspace(line[i]))
		return (!ft_isspace(line[i + 1]));
	if (ft_isspace(line[i + 1]))
		return (TRUE);
	if (ft_isset(line[i], "><|;&"))
	{
		if (line[i] != line[i + 1])
			return (TRUE);
		return ((tool->prev == line[i] && tool->start != i) ? TRUE : FALSE);
	}
	return (ft_isset(line[i + 1], "><|;&") ? TRUE : FALSE);
}

char			**tokenizer(char *line)
{
	t_tokenizer		tool;
	char			*token;
	char			**tokens;

	tokens = 0;
	tab_init(&tool);
	while (line[tool.idx])
	{
		token = 0;
		if (is_start(line, &tool))
			tool.start = tool.idx;
		if (is_end(line, &tool))
		{
			token = ft_strsub(line, tool.start, tool.idx - tool.start + 1);
			ft_realloc_doublestr(&tokens, token);
			ft_free_str(&token);
			tool.start = -1;
			tool.prev = 0;
		}
		tool.idx++;
	}
	return (tokens);
}
