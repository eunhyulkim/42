/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:03:18 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/06 18:38:59 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

//TODO: add feature to take care of 'fd>' pattern.
//TODO: check close location and fd
int	execute_redirection(t_job *job, int pipes[2])
{
	t_redir	*redir_list;
	int		fd;

	if (!job || !(redir_list = job->redir_list))
		return (FALSE);
	while (redir_list)
	{
		if (*(redir_list->sign) == '>')
		{
			if ((fd = open(redir_list->arg, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
				return (FALSE);
			close(pipes[1]);
			pipes[1] = fd;
			dup2(pipes[1], redir_list->fd);
		}
		else if (*(redir_list->sign) == '<')
		{
			if ((fd = open(redir_list->arg, O_RDWR)) < 0)
			{
				printf("mongshell$ %s : No such file or directory\n", redir_list->arg);
				return (FALSE);
			}
			close(pipes[0]);
			pipes[0] = fd;
		}
		redir_list = redir_list->next;
	}
	return (TRUE);
}

int			count_job(t_job *job)
{
	int	i;

	i = 0;
	while (job)
	{ i++;
		job = job->next;
	}
	return (i);
}

int			*make_pipes(t_job *job)
{
	int		*pipes;
	int		job_count;
	int		pipe_count;
	int		i;

	job_count = count_job(job);
	pipe_count = job_count > 1 ? job_count - 1 : 0;
	if (!pipe_count)
		return NULL;
	if (!(pipes = ft_calloc(sizeof(int), pipe_count * 3)))
	{
		printf("malloc error\n");
		return NULL;
	}
	i = -1;
	while (i++ < pipe_count)
		pipe(&pipes[i * 2]);
	return (pipes);
}



//========================temp codes to make builtin cmds========================

static int		execute_single_job(t_job *job)
{
	t_command *command;

	if (!job)
		return (TRUE);
	command = &job->command;
	if (!ft_strcmp(command->cmd, "echo"))
		cmd_echo(command);
	else if (!ft_strcmp(command->cmd, "env"))
		cmd_env(command);
	else if (!ft_strcmp(command->cmd, "pwd"))
		cmd_pwd(command);
	else if (!ft_strcmp(command->cmd, "export"))
		cmd_export(command);
	else if (!ft_strcmp(command->cmd, "unset"))
		cmd_unset(command);
	else if (!ft_strcmp(command->cmd, "exit"))
		return (cmd_exit(command));
	return (TRUE);
}

static int	execute_redirection(t_job *job, int pipes[2])
{
	t_redir	*redir_list;
	int		fd;

	if (!job || !(redir_list = job->redir_list))
		return (FALSE);
	while (redir_list)
	{
		if (*(redir_list->sign) == '>')
		{
			if ((fd = open(redir_list->arg, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
				return (FALSE);
			close(pipes[1]);
			pipes[1] = fd;
			dup2(pipes[1], redir_list->fd);
		}
		else if (*(redir_list->sign) == '<')
		{
			if ((fd = open(redir_list->arg, O_RDWR)) < 0)
			{
				printf("mongshell$ %s : No such file or directory\n", redir_list->arg);
				return (FALSE);
			}
			close(pipes[0]);
			pipes[0] = fd;
		}
		redir_list = redir_list->next;
	}
	return (TRUE);
}


//TODO: add execute_redirection
//TODO: test pipe cases
//TODO: add signals
//TODO: close functions
static void		old_execute_job(t_job *job)
{
	pid_t	pid;
	int		*pipes;
	int		i;

	if (!job)
		return ;
	pipes = make_pipes(job);
	i = 0;
	while (job)
	{
		printf("parent PID: %d\n", getpid());
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Fork error\n", 2);
			break;
		}
		else if (pid == 0)
		{
			if (i != 0)							// if not first job
				dup2(pipes[(i - 1) * 2], 1);
			if (job->next)						// if not last job
				dup2(pipes[i * 2 + 1], 0);
			printf("child PID: %d\n", getpid());
			execute_command(&job->command);
		}
		else
			job = job->next;
		i++;
	}
}

int		execute_table(t_table *table)
{
	int res;
	
	res = TRUE;
	if (table->sep_type == AND && g_res == TRUE)
		res = execute_job(table->job_list);
	else if (table->sep_type == OR && g_res == FALSE)
		res = execute_job(table->job_list);
	else if (table->sep_type == SEMI || table->sep_type == START)
		res = execute_job(table->job_list);
	return (res);
}