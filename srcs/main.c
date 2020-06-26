#include "minishell.h"

static void		excute_line(char *line)
{
	char	**tokens;

	tokens = lexer(line);
	table = parser(tokens);
	ft_free_doublestr(tokens);
	if (!excute_redirects(table))
		return ;
	excute_commands(table);
}

int				main(int ac, char *av[], char **env)
{
	char	**lines;

	display_logo();
	init_env(env);

	while (TRUE)
	{
		display_prompt();
		if (!(lines = readlines()))
			continue;
		while (*lines)
			excute_line(*lines++);
		free(lines);
	}
	ft_free_doublestr(g_env);
	return (0);
}
