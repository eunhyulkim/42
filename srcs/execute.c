/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:03:18 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/09 12:37:56 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

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
	int		pipe_count;
	int		i;

	if (!(pipe_count = count_job(job) - 1))
		return (0);
	if (!(g_pipes = (int *)ft_calloc(sizeof(int), pipe_count * 2)))
		return (0);
	i = 0;
	while (i < pipe_count)
	{
		pipe(&g_pipes[i * 2]);
		i++;
	}
	return (g_pipes);
}

static void		save_standard_fd(t_table *table)
{
	table->fd[0] = dup(0);
	table->fd[1] = dup(1);
	g_stdin = table->fd[1];
	table->fd[2] = dup(2);
}

static void		restore_standard_fd(t_table *table)
{
	dup2(table->fd[0], 0);
	dup2(table->fd[1], 1);
	g_stdin = 1;
	dup2(table->fd[1], 2);
	close(table->fd[0]);
	close(table->fd[1]);
	close(table->fd[2]);
}

static void		dup_pipe(t_job *job, int pidx)
{
	if (pidx == 0 && !job->next)
		return ;
	if (pidx == 0)
	{
		dup2(g_pipes[pidx * 2 + 1], 1);
	}
	else if (!(job->next))
		dup2(g_pipes[(pidx - 1) * 2], 0);
	else
	{
		dup2(g_pipes[(pidx - 1) * 2], 0);
		dup2(g_pipes[pidx * 2 + 1], 1);
	}
}

static int			get_fd(t_redir *redir)
{
	int		fd;

	fd = -1;
	if (!redir->arg)
		return (-2);
	if (!(ft_strcmp(redir->sign, ">")))
		fd = open(redir->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!(ft_strcmp(redir->sign, ">>")))
		fd = open(redir->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!(ft_strcmp(redir->sign, "<")))
		fd = open(redir->arg, O_RDWR);
	else if (!(ft_strcmp(redir->sign, "<<")))
		fd = open(TEMP_PATH, O_RDWR);
	if (fd > g_maxfd)
		g_maxfd = fd;
	return (fd);
}

static int		excute_redirection(t_table *table, t_job *job)
{
	t_redir *redir;
	int		fd;

	if (!(job->next))
	{
		dup2(table->fd[1], 1);
		dup2(table->fd[2], 2);
	}
	if (!(redir = job->redir_list))
		return (1);
	while (redir)
	{
		if ((fd = get_fd(redir)) >= 0)
		{
			if (*(redir->sign) == '>')
				dup2(fd, redir->fd);
			else
				dup2(fd, 0);
		}
		else if (fd == -2)
		{
			g_res = 1;
			ft_putstr_fd("mongshell: ", 1);
			ft_putstr_fd(redir->arg, 1);
			ft_putendl_fd(": ambiguous redirect", 1);
			return (0);
		}
		else
		{
			g_res = 1;
			ft_putstr_fd("mongshell: ", 1);
			ft_putstr_fd(redir->arg, 1);
			ft_putendl_fd(": No such file or directory", 1);
			return (0);
		}
		redir = redir->next;
	}
	return (1);
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
	else
		cmd_execve(command);
	return (TRUE);
}

static int		execute_job(t_table *table, t_job *job)
{
	int		pidx;

	pidx = 0;
	while (job)
	{
		dup_pipe(job, pidx);
		if (!excute_redirection(table, job))
		{
			job = job->next;
			continue;
		}
		if (!(execute_command(&job->command)))
			return (FALSE);
		pidx++;
		job = job->next;
	}
	return (TRUE);
}

void	close_fd_and_pipes(void)
{
	while (g_maxfd > 2)
		close(g_maxfd--);
	ft_free(g_pipes);
}

int			execute_table(t_table *table)
{
	int 	res;
	int		status;

	if (!table || !table->job_list || !table->job_list->command.cmd)
		return (1);
	save_standard_fd(table);
	g_pipes = make_pipes(table->job_list);
	res = TRUE;
	if (table->sep_type == AND && g_res == TRUE)
		res = execute_job(table, table->job_list);
	else if (table->sep_type == OR && g_res == FALSE)
		res = execute_job(table, table->job_list);
	else if (table->sep_type == SEMI || table->sep_type == START)
		res = execute_job(table, table->job_list);
	while (wait(&status) > 0)
		;
	g_res = WEXITSTATUS(status);
	restore_standard_fd(table);
	close_fd_and_pipes();
	return (res);
}
