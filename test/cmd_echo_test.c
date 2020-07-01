#include "minishell.h"

t_table				*make_test_table(void)
{
	t_table		*test_table;
	t_command	*cmd1;
	t_command	*cmd2;
	t_redi		*redi1;
	t_redi		*redi2;
	char		**argu_list1;

	test_table = (t_table *)malloc(sizeof(t_table) * 1);
	cmd1 = (t_command *)malloc(sizeof(t_command) * 1);
	cmd2 = (t_command *)malloc(sizeof(t_command) * 1);
	redi1 = (t_redi *)malloc(sizeof(t_redi) * 1);
	redi2 = (t_redi *)malloc(sizeof(t_redi) * 1);
	argu_list1 = (char **)malloc(sizeof(char *) * 3);

	test_table->cmd_list = cmd1;
	test_table->redi_list = redi1;
	test_table->input_fd = 0;
	test_table->output_fd = 1;

	/*
	//cmd_echo test 1
	cmd1->cmd = "echo";
	argu_list1[0] = "abc";
	argu_list1[1] = NULL;
	cmd1->argu_list = argu_list1;
	cmd1->next = NULL;

	redi1 = NULL;
	*/

	/*
	//cmd_echo test 2
	cmd1->cmd = "echo";
	argu_list1[0] = "abc";
	argu_list1[1] = "ABCD";
	argu_list1[2] = NULL;
	cmd1->argu_list = argu_list1;
	cmd1->next = NULL;

	redi1 = NULL;
	*/

	/*
	//cmd_echo test 3
	cmd1->cmd = "echo";
	argu_list1[0] = "abc";
	argu_list1[1] = "ABCD";
	argu_list1[2] = NULL;
	cmd1->argu_list = argu_list1;
	cmd1->next = NULL;

	redi1->redi = ">";
	redi1->argu = "r.txt";
	redi1->next = redi2;

	redi2->redi = ">";
	redi2->argu = "r123.txt";
	redi2->next = NULL;
	*/

	/*
	//cmd_echo test 4
	cmd1->cmd = "echo";
	argu_list1[0] = "-n";
	argu_list1[1] = "ABCD";
	argu_list1[2] = NULL;
	cmd1->argu_list = argu_list1;
	cmd1->next = NULL;

	redi1->redi = ">";
	redi1->argu = "r.txt";
	redi1->next = redi2;

	redi2->redi = ">";
	redi2->argu = "r123.txt";
	redi2->next = NULL;
	*/

	//cmd_echo test 5
	cmd1->cmd = "echo";
	argu_list1[0] = NULL;
	cmd1->argu_list = argu_list1;
	cmd1->next = NULL;

	redi1->redi = ">";
	redi1->argu = "r.txt";
	redi1->next = redi2;

	redi2->redi = ">";
	redi2->argu = "r123.txt";
	redi2->next = NULL;

	test_table->next = NULL;
	return (test_table);
}

int				test_table(t_table *table)
{
	t_command	*cmd_list;
	t_redi		*redi_list;

	cmd_list = table->cmd_list;
	redi_list = table->redi_list;
	while (cmd_list)
	{
		printf("%s\n", cmd_list->cmd);
		printf("%s\n", cmd_list->argu_list[0]);
		cmd_list = cmd_list->next;
	}

	while (redi_list)
	{
		printf("%s\n", redi_list->redi);
		printf("%s\n", redi_list->argu);
		redi_list = redi_list->next;
	}
	return (0);
}

void		execute_command(t_command *cmd_list)
{
	if (!ft_strcmp(cmd_list->cmd, "echo"))
		cmd_echo(cmd_list);
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
	//test_table(table);

	execute_redirection(table);
	printf("output_fd: %d\n", table->output_fd);
	printf("input_fd: %d\n", table->input_fd);
	dup2(table->output_fd, 1);
	execute_command(table->cmd_list);
}

int				main(int ac, char *av[], char **env)
{
	char	*line;
	int		idx;

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
		idx = 0;
		process_line(line);
		free(line);
	}
	ft_free_doublestr(g_env);
	return (0);
}
