/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:45:07 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/30 13:02:04 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		tab_init(t_tokenizer *tab)
{
	tab->idx = 0;
	tab->start = -1;
	tab->prev = 0;
	tab->quote = 0;
}

static char 	get_quote(char *line, int idx)
{
	char	quote;

	quote = 0;
	if (line[idx] == '\'')
		quote = '\'';
	else if (line[idx] == '\"')
		quote = '\"';
	return (quote);
}

static	int		is_start(char *line, t_tokenizer *tab)
{
	int		i;

	i = tab->idx;
	if (!line || !line[i] || tab->quote)
		return (FALSE);
	tab->quote = get_quote(line, i);
	if (line[i] == '\n')
		return (TRUE);
	if (ft_isspace(line[i]))
		return (ft_isspace(line[i - 1]) ? FALSE : TRUE);
	if (ft_isset(line[i], "><|;&"))
	{
		if (tab->prev == line[i])
			return (FALSE);
		tab->prev = line[i];
		return (TRUE);
	}
	tab->prev = 0;
	if (!tab->idx)
		return (TRUE);
	return (ft_isspace(line[i - 1]) || ft_isset(line[i - 1], "><|;&"));
}

static	int		is_end(char *line, t_tokenizer *tab)
{
	int		i;

	i = tab->idx;
	if (!line || tab->start == -1)
		return (FALSE);
	if (line[i] == tab->quote && tab->start != i)
		tab->quote = 0;
	if (!line[i + 1] || (!tab->quote && line[i] == '\n'))
		return (TRUE);
	if (tab->quote)
		return (FALSE);
	if (ft_isspace(line[i]))
		return (!ft_isspace(line[i + 1]));
	if (ft_isspace(line[i + 1]))
		return (TRUE);
	if (ft_isset(line[i], "><|;&"))
	{
		if (line[i] != line[i + 1])
			return (TRUE);
		return ((tab->prev == line[i] && tab->start != i) ? TRUE : FALSE);
	}
	return (ft_isset(line[i + 1], "><|;&") ? TRUE : FALSE);
}

char			**tokenizer(char *line)
{
	t_tokenizer		tab;
	char			*token;
	char			**tokens;

	tokens = 0;
	tab_init(&tab);
	while (line[tab.idx])
	{
		if (is_start(line, &tab))
			tab.start = tab.idx;
		if (is_end(line, &tab))
		{
			token = ft_strsub(line, tab.start, tab.idx - tab.start + 1);
			ft_realloc_doublestr(&tokens, token);
			free(token);
			tab.start = -1;
			tab.prev = 0;
		}
		tab.idx++;
	}
	return (tokens);
}
