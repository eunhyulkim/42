#include "minishell.h"
#include "execute.h"

static void		process_line(char *line)
{
	char		**tokens;
	t_table		*table;
	t_table		*first_table;

	tokens = tokenizer(line);
	if (!lexer(tokens) || !(table = parser(tokens)))
		return ;
	if (DEBUG_ALL || DEBUG_CONVERT || !DEBUG_TABLE)
		converter(table);
	if (DEBUG_ALL || DEBUG_TABLE || DEBUG_CONVERT)
		print_table(table);
	if (!(table = parser(tokens)))
	 	return ;
	first_table = table;
	while (table)
	{
	//	converter(table);
		execute_table_with_single_job(table);
		wait(NULL);
		table = table->next;
	}
	ft_free_doublestr(tokens);
	free_table(first_table);
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
