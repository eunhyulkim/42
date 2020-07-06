/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:03:18 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/06 20:25:41 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

//TODO: add execute_redirection
//TODO: test pipe cases
//TODO: add signals
//TODO: close functions
// void	old_execute_job(t_job *job, int *pipes)
// {
// 	pid_t	pid;
// 	int		i;
	
// 	i = 0;
// 	while (job)
// 	{
// 		printf("parent PID: %d\n", getpid());
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			ft_putstr_fd("Fork error\n", 2);
// 			break;
// 		}
// 		else if (pid == 0)
// 		{
// 			if (i != 0)							// if not first job
// 				dup2(pipes[(i - 1) * 2], 1);
// 			if (job->next)						// if not last job
// 				dup2(pipes[i * 2 + 1], 0);
// 			printf("child PID: %d\n", getpid());
// 			// execute_command(&job->command);
// 		}
// 		else
// 			job = job->next;
// 		i++;
// 	}
// }

// void	old_execute_command(t_command *command)
// {
// 	//TODO: add commands
// 	if (!ft_strcmp(command->cmd, "echo"))
// 		cmd_echo(command);
// 	else if (!ft_strcmp(command->cmd, "env"))
// 		cmd_env(command);
// 	else if (!ft_strcmp(command->cmd, "pwd"))
// 		cmd_pwd(command);
// 	else if (!ft_strcmp(command->cmd, "export"))
// 		cmd_export(command);
// 	else
// 		exit(0);
// }

// int		old_execute_redirection(t_job *job, int pipes[2])
// {
// 	t_redir	*redir_list;
// 	int		fd;

// 	if (!job || !(redir_list = job->redir_list))
// 		return (FALSE);
// 	while (redir_list)
// 	{
// 		if (*(redir_list->sign) == '>')
// 		{
// 			if ((fd = open(redir_list->arg, O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
// 				return (FALSE);
// 			close(pipes[1]);
// 			pipes[1] = fd;
// 			dup2(pipes[1], redir_list->fd);
// 		}
// 		else if (*(redir_list->sign) == '<')
// 		{
// 			if ((fd = open(redir_list->arg, O_RDWR)) < 0)
// 			{
// 				printf("mongshell$ %s : No such file or directory\n", redir_list->arg);
// 				return (FALSE);
// 			}
// 			close(pipes[0]);
// 			pipes[0] = fd;
// 		}
// 		redir_list = redir_list->next;
// 	}
// 	return (TRUE);
// }

//========================temp codes to make builtin cmds========================

static int			count_job(t_job *job)
{
	int		cnt;

	cnt = 0;
	while (job)
	{
		cnt++;
		job = job->next;
	}
	return (cnt);
}

static int			*make_pipes(t_job *job)
{
	int		*pipes;
	int		pipe_count;
	int		i;

	if (!(pipe_count = count_job(job) - 1))
		return (0);
	if (!(pipes = ft_calloc(sizeof(int), pipe_count * 2)))
		return (0);
	i = 0;
	while (i < pipe_count)
	{
		pipe(&pipes[i * 2]);
		i++;
	}
	return (pipes);
}

static void		save_standard_fd(t_table *table)
{
	table->fd[0] = dup(0);
	table->fd[1] = dup(1);
	table->fd[2] = dup(2);
}

static void		restore_standard_fd(t_table *table)
{
	dup2(table->fd[0], 0);
	dup2(table->fd[1], 1);
	dup2(table->fd[1], 2);
	close(table->fd[0]);
	close(table->fd[1]);
	close(table->fd[2]);
}

static void		dup_pipe(t_job *job, int *pipes, int pidx)
{
	if (pidx == 0 && !job->next)
		return ;
	if (pidx == 0)
		dup2(pipes[pidx * 2 + 1], 1);
	else if (!(job->next))
		dup2(pipes[pidx * 2], 0);
	else
	{
		dup2(pipes[pidx * 2], 0);
		dup2(pipes[pidx * 2 + 1], 1);
	}
}

static int			get_fd(t_redir *redir)
{
	int		fd;
	
	fd = -1;
	if (!(ft_strcmp(redir->sign, ">")))
		fd = open(redir->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!(ft_strcmp(redir->sign, ">>")))
		fd = open(redir->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!(ft_strcmp(redir->sign, "<")))
		fd = open(redir->arg, O_RDWR);
	// else if (!(ft_strcmp(redir->sign, "<<")))
	// 	fd = open(TEMP_PATH, O_RDWR);
	return (fd);
}

static void		excute_redirection(t_table *table, t_job *job)
{
	t_redir *redir;
	int		fd;

	if (!(redir = job->redir_list))
		return ;
	if (!(job->next))
	{
		dup2(table->fd[1], 1);
		dup2(table->fd[2], 2);
	}	
	while (redir)
	{
		if ((fd = get_fd(redir)) < 0)
			return ;
		if (*(redir->sign) == '>')
			dup2(fd, redir->fd);
		else
			dup2(fd, 0);
		redir = redir->next;
	}
}

static int		execute_command(t_command *command)
{
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
	else if (!ft_strcmp(command->cmd, "cd"))
		cmd_cd(command);
	else if (!ft_strcmp(command->cmd, "exit"))
		return (cmd_exit(command));	
	return (TRUE);
}

static int		execute_job(t_table *table, t_job *job, int *pipes)
{
	int		pidx;
	
	pidx = 0;
	while (job)
	{
		dup_pipe(job, pipes, pidx);
		excute_redirection(table, job);
		if (!(execute_command(&job->command)))
			return (FALSE);
		job = job->next;
	}
	return (TRUE);
}

int			execute_table(t_table *table)
{
	int		*pipes;
	int 	res;
	
	if (!table || !table->job_list)
		return (1);
	save_standard_fd(table);
	pipes = make_pipes(table->job_list);
	res = TRUE;
	if (table->sep_type == AND && g_res == TRUE)
		res = execute_job(table, table->job_list, pipes);
	else if (table->sep_type == OR && g_res == FALSE)
		res = execute_job(table, table->job_list, pipes);
	else if (table->sep_type == SEMI || table->sep_type == START)
		res = execute_job(table, table->job_list, pipes);
	// close_pipes(pipes);
	restore_standard_fd(table);
	return (res);
}
