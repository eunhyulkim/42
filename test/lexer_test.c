#include "minishell.h"

static void		process_line(char *line)
{
	char		**tokens;
	// t_table		*table;

	write(1, "\n", 1);
	if (!(tokens = tokenizer(line)))
		return ;
	int i = 0;
	while (tokens && tokens[i])
	{
		if (!ft_strcmp(tokens[i], "\n"))
		{
			printf("[\\n]");
			i++;
		}
		else
			printf("[%s]", tokens[i++]);
	}
	printf("\n");
	lexer(tokens);
	ft_free_doublestr(tokens);
}

int				main(int ac, char *av[], char **env)
{
	display_logo();
	init_env(env);

	(void)ac;
	(void)av;
	printf("[LEXER RESULT]\n");
	// process_line("|||||\n");
	// process_line("&&&&&\n");
	// process_line(";;;;;\n");
	// process_line("|\n");
	// process_line("a|\n");
	// process_line(" |\n");
	// process_line("a |\n");
	// process_line("|b\n");
	// process_line("| \n");
	// process_line("| b\n");
	// process_line("a|b\n");
	// process_line("a | b\n");
	// process_line("a| b\n");
	// process_line("a |b\n");
	// process_line("a | \n");
	// process_line("a| \n");
	// process_line(" | b\n");
	// process_line(" |b\n");
	// process_line("a | ;\n");
	// process_line("a |;\n");
	// process_line("a|;\n");
	// process_line("a| ;\n");
	// process_line(";| a\n");
	// process_line(";|a\n");
	// process_line("; |a\n");
	// process_line("; | a\n");
	// process_line("; | ;\n");
	// process_line("; |;\n");
	// process_line(";| ;\n");
	// process_line(";|;\n");
	// process_line("|||;\n");
	// process_line("a| ");
	// process_line("a\"| \"'str");
	// process_line("a\"str| \" 'str");

	process_line("& test");
	process_line("&& test");
	process_line("| test");
	process_line("|| test");
	ft_free_doublestr(g_env);
	return (0);
}
