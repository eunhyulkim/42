#include "minishell.h"
#include "execute.h"

static int		process_line(char *line)
{
	char		**tokens;
	t_table		*table;
	t_table		*first_table;

	tokens = tokenizer(line);
	if (!lexer(tokens) || !(table = parser(tokens)))
		return (TRUE);
	first_table = table;
	while (table)
	{
		expander(table);
		if (DEBUG_ALL || DEBUG_CONVERT || !DEBUG_TABLE)
			converter(table);
		if (!execute_table(table))
		{
			ft_free_doublestr(tokens);
			free_table(first_table);
			return (FALSE);
		}
		table = table->next;
	}
	if (DEBUG_ALL || DEBUG_TABLE || DEBUG_CONVERT)
		print_table(first_table);
	ft_free_doublestr(tokens);
	free_table(first_table);
	return (TRUE);
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
		if (!get_next_line(0, &line))
			continue;
		if (ft_strcmp(line, "\n") && !process_line(line))
			break ;
		free(line);
	}
	ft_free_doublestr(g_env);
	return (0);
}
