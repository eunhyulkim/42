#include "minishell.h"
#include "execute.h"
#include "lexer.h"

t_table	*make_test_table(void)
{
	t_table	*table1;
	t_table	*table2;
	t_table	*table3; t_job	*job1;
	t_job	*job2;
	t_job	*job3;
	char	**arg_list1;
	char	**arg_list2;
	char	**arg_list3;

	table1 = (t_table *)malloc(sizeof(t_table) * 1);
	table2 = (t_table *)malloc(sizeof(t_table) * 1);
	table3 = (t_table *)malloc(sizeof(t_table) * 1);

	job1 = (t_job *)malloc(sizeof(t_job) * 1);
	job2 = (t_job *)malloc(sizeof(t_job) * 1);
	job3 = (t_job *)malloc(sizeof(t_job) * 1);

	arg_list1 = (char **)malloc(sizeof(char *) * 2);
	arg_list2 = (char **)malloc(sizeof(char *) * 2);
	arg_list3 = (char **)malloc(sizeof(char *) * 2);

	//set job1
	job1->command.cmd = "echo";
	arg_list1[0] = "AAA";
	arg_list1[1] = NULL;
	job1->command.arg_list = arg_list1;
	job1->redir_list = NULL;
	job1->next = NULL;

	//set job2
	job2->command.cmd = "echo";
	arg_list2[0] = "BBB";
	arg_list2[1] = NULL;
	job2->command.arg_list = arg_list2;
	job2->redir_list = NULL;
	job2->next = NULL;

	//set job3
	job3->command.cmd = "echo";
	arg_list3[0] = "CCC";
	arg_list3[1] = NULL;
	job3->command.arg_list = arg_list3;
	job3->redir_list = NULL;
	job3->next = NULL;

	//set table1
	table1->sep_type = SEMI;
	table1->job_list = job1;
	table1->next = table2;

	//set table2
	table2->sep_type = SEMI;
	table2->job_list = job2;
	table2->next = table3;

	//set table3
	table3->sep_type = SEMI;
	table3->job_list = job3;
	table3->next = NULL;

	return (table1);
}

static void		process_line(char *line)
{
	(void)line;
	// char		**tokens;
	// t_table		*table;

	// if (!(tokens = lexer(line)))
	// 	return ;
	// if (!(table = parser(tokens)))
	// 	return ;
	// ft_free_doublestr(tokens);
	t_table *table;
	
	table = make_test_table();
	execute_table_with_single_job(table);
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
		int fd;
		if (!(fd = get_next_line(1, &line)))
			continue;
		process_line(line);
		free(line);
	}
	ft_free_doublestr(g_env);
	return (0);
}
