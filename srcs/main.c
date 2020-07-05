#include "minishell.h"

static void		process_line(char *line)
{
	char		**tokens;
	t_table		*table;
	t_table		*start;

	tokens = tokenizer(line);
	if (!lexer(tokens) || !(table = parser(tokens)))
		return ;
	start = table;
	while (table)
	{
		if (DEBUG_ALL || DEBUG_CONVERT || !DEBUG_TABLE)
			converter(table);
		// excute_table(table);
		// wait(NULL);
		table = table->next;
	}
	if (DEBUG_ALL || DEBUG_TABLE || DEBUG_CONVERT)
		print_table(start);
	ft_free_doublestr(tokens);
	free_table(start);
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
