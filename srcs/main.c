#include "minishell.h"

static void		excute_line(char *line)
{
	char		**tokens;
	// t_table		*table;

	tokens = tokenizer(line);
	// if (!(tokens = lexer(line)))
	// 	return ;
	// if (!(table = parser(tokens)))
	// 	return ;
	// ft_free_doublestr(tokens);
	// if (!excute_redirects(table))
	// 	return ;
	// excute_commands(table);
}

int				main(int ac, char *av[], char **env)
{
	char	*line;

	display_logo();
	init_env(env);

	(void)ac;
	(void)av;
	while (TRUE)
	{
		display_prompt();
		line = 0;
		if (!(get_next_line(1, &line)))
			continue;
		process_line(line);
		free(line);
	}
	ft_free_doublestr(g_env);
	return (0);
}
