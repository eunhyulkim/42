#include "minishell.h"
#include "lexer.h"

static void		print_table(t_table *table)
{
	t_job	*job;
	t_redir	*redir;
	char	**arg;
	int		idx;

	if (!table)
		return ;
	while (table)
	{
		printf("\n");
		if (!table->sep_type)
			printf("['START' ");
		else if (table->sep_type == AND)
			printf("['AND' ");
		else if (table->sep_type == OR)
			printf("['OR' ");
		else if (table->sep_type == SEMI)
			printf("['SEMI' ");
		printf("TABLE PRINT]\n");
		job = table->job_list;
		while (job)
		{
			printf("\n>_____JOB_____<\n");
			printf("cmd: %s\n", job->command.cmd);
			printf("arg:[");
			arg = job->command.arg_list;
			idx = 0;
			while (arg && arg[idx])
			{
				printf("%s,", arg[idx]);
				idx++;
			}
			printf("]\n");
			if (!job->redir_list)
				printf("redir: NULL\n");
			else
			{
				redir = job->redir_list;
				while (redir)
				{
					printf("redir->sign: %s\n", redir->sign);
					printf("redir->fd: %d\n", redir->fd);
					printf("redir->arg: %s\n", redir->arg);
					redir = redir->next;
				}
			}
			printf("job_fd: [%d][%d]\n", job->fd[0], job->fd[1]);
			job = job->next;
		}
		table = table->next;
	}
}

static void		process_line(char *line)
{
	char		**tokens;
	t_table		*table;

	tokens = tokenizer(line);
	if (!(lexer(tokens)))
		return ;
	table = parser(tokens);
	// if (!(table = parser(tokens)))
	// 	return ;
	// while (1)
	// 	;
	print_table(table);
	ft_free_doublestr(tokens);
	free_table(table);
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
	exit(0);
}
