#include "minishell.h"

static void		excute_line(char *line)
{
	char		**tokens;
	t_table		*table;

	if (!(tokens = lexer(line)))
		return ;
	if (!(table = parser(tokens)))
		return ;
	ft_free_doublestr(tokens);
	if (!excute_redirects(table))
		return ;
	excute_commands(table);
}

int				main(int ac, char *av[], char **env)
{
	char	**lines;
	int		idx;

	display_logo();
	init_env(env);

	while (TRUE)
	{
		display_prompt();
		lines = 0;
		if (!(lines = readlines()))
			continue;
		idx = 0;
		while (lines[idx])
			excute_line(lines[idx++]);
		ft_free_doublestr(lines);
	}
	ft_free_doublestr(g_env);
	return (0);
}
