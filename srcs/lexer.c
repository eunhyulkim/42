#include "minishell.h"

static void		tab_init(t_lexer_tab *tab)
{
	tab->idx = 0;
	tab->start = -1;
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

static	int		is_start(char *line, t_lexer_tab *tab)
{
	if (!line || !line[tab->idx])
		return (FALSE);
	if (tab->quote || ft_isspace(line[tab->idx]))
		return (FALSE);
	tab->quote = get_quote(line, tab->idx);
	if (tab->idx && !ft_isspace(line[tab->idx - 1]))
		return (FALSE);
	return (TRUE);
}

static	int		is_end(char *line, t_lexer_tab *tab)
{
	int		j;

	if (!line || tab->start == -1 || ft_isspace(line[tab->idx]))
		return (FALSE);
	if (line[tab->idx] == tab->quote && tab->start != tab->idx)
		tab->quote = 0;
	if (!line[tab->idx + 1])
		return (TRUE);
	if (tab->quote)
		return (FALSE);
	if (ft_isspace(line[tab->idx + 1] || ft_isset(line[tab->idx + 1], "><")))
		return (TRUE);
	if (!ft_isnum(line[tab->idx + 1]))
		return (FALSE);
	j = 2;
	while (ft_isnum(line[tab->idx + j]))
		j++;
	if (ft_isset(line[tab->idx + j], "><"))
		return (TRUE);
	return (FALSE);
}

char			**lexer(char *line)
{
	t_lexer_tab		tab;
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
			tab.quote = 0;
		}
		tab.idx++;
	}
	return (tokens);
}
