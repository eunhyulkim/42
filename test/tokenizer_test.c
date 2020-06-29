#include "minishell.h"

static void		process_line(char *line)
{
	char		**tokens;
	// t_table		*table;

	tokens = tokenizer(line);
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
	free(tokens);
}

int				main(int ac, char *av[], char **env)
{
	display_logo();
	init_env(env);

	(void)ac;
	(void)av;
	printf("[TOKENIZING RESULT]\n");
	process_line("");
	process_line("  ");
	process_line("NORMAL_TEXT");
	process_line("NORMAL TEXT  ");
	process_line("NO;RMAL");
	process_line("NO;;RMAL");
	process_line("NO;;;RMAL");
	process_line("NO&&&&&RMAL");
	process_line("NO&&|||&RMAL");
	process_line("NO;|;RMAL");
	process_line("NO& &&|&&RMAL");
	process_line("\'asd'");
	process_line("\'as\'\"d\"");
	process_line("\'as\' \"d\"");
	process_line("\'as\' \"d\"\n");
	process_line("\'as;\' |\"d|\"& \n");
	process_line("\'as;\' |\"d|& \n");
	printf("'\n'");
	process_line(">213 \n adsf < || dk &&sdahjf1>2><3\a 1> a 2>>> b");
	ft_free_doublestr(g_env);
	return (0);
}
