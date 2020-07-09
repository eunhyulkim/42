#include "minishell.h"
#include "execute.h"

static int		process_line(char *line)
{
	char		**tokens;
	t_table		*table;
	t_table		*first_table;

	if (*line == '\n')
		return (TRUE);
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
	init_env(ac, av, env);
	while (TRUE)
	{
		signal(SIGINT, (void *)signal_handler);
		signal(SIGQUIT, (void *)signal_handler);
		display_prompt();
		line = 0;
		if (!(get_next_line(0, &line)))
		{
			free(line);
			ft_putstr_fd("exit\n", 1);
			break;
		}
		if (ft_strcmp(line, "\n") && !process_line(line))
			break ;
		free(line);
	}
	ft_free_doublestr(g_env);
	return (0);
}
