#include "minishell.h"

int	execute_redirection(t_table *table)
{
	t_redir	*redi_list;
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

//TODO: make complete structure. This is just draft.
 //int	execute_command_list(t_table *table)
 //{
 //	t_command	*cmd;
 //	pid_t		pid;
 //	int			fd[2];
 //	int			input_fd;
 //
 //	cmd = table->cmd;
 //	whlie (cmd != NULL)
 //	{
 //		pipe(fd);
 //		if ((pid = fork()) == -1)
 //		{
 //			ft_putstr_fd("Pid error\n", 2);
 //			return (FALSE);
 //		}
 //		else if (pid == 0)
 //		{
 //			dup2(fd[1], 1);
 //			if (*(cmd + 1) != NULL)
 //				dup2(fd[1], 1);
 //			close(fd[0]);
 //			if (run_cmd(cmd) == -1)
 //			{
 //				printf("mongshell: %s: command not found", cmd->cmd);
 //				return (FALSE);
 //			}
 //			exit();
 //		}
 //		else
 //		{
 //			wait(NULL);
 //			close(fd[1]);
 //			input_fd = p[0];
 //			cmd = cmd->next;
 //		}
 //	}
 //	return (TRUE);
 //}
