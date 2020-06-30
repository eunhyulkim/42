#include "minishell.h"

int	execute_redirection(t_table *table)
{
	t_redi	*redi_list;
	int		fd;

	if (!table || !(redi_list = table->redi_list))
		return (0);
	while (redi_list)
	{
		if (*(redi_list->redi) == '>')
		{
			if ((fd = open(redi_list->argu, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
				return (0);
			table->output_fd = fd;
		}
		else if (*(redi_list->redi) == '<')
		{
			if ((fd = open(redi_list->argu, O_RDWR)) < 0)
			{
				//TODO: make error command
				printf("mongshell$ %s : No such file or directory\n", redi_list->argu);
				return (0);
			}
			table->input_fd = fd;
		}
		redi_list = redi_list->next;
	}
	return (1);
}

int	execute_command(t_table *table)
{
	t_command	*cmd;
	pid_t		pid;
	int			fd[2];

	cmd = table->cmd;
	set_fd(fd);
	if ((pid = fork()) < 0)
	{
		ft_putstr_fd("Pid error\n", 2);
		return (0);
	}
	if (pid == 0)
	{

	}
	else
	{
	}
	return (1);
}
