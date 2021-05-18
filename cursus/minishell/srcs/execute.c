/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:03:18 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/11 20:20:59 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		execute_redirection(t_table *table, t_job *job)
{
	t_redir *redir;
	int		fd;

	if (!(job->next))
		redirect_stdout_fd(table);
	if (!(redir = job->redir_list))
		return (1);
	while (redir)
	{
		if ((fd = get_fd(redir)) >= STDNRM)
			dup2(fd, redir->fd);
		else if (fd == REDIRAMB)
			error_execute(redir->arg, REDIR_AMBIGOUS, 1);
		else if (fd == FDERR)
			error_execute(redir->arg, NO_SUCH_ENTRY, 1);
		if (fd == REDIRAMB || fd == FDERR)
			return (0);
		redir = redir->next;
	}
	return (1);
}

static void		execute_command(t_command *command)
{
	if (!ft_strcmp(command->cmd, "echo"))
		cmd_echo(command);
	else if (!ft_strcmp(command->cmd, "env"))
		cmd_env(command);
	else if (!ft_strcmp(command->cmd, "pwd"))
		cmd_pwd();
	else if (!ft_strcmp(command->cmd, "export"))
		cmd_export(command);
	else if (!ft_strcmp(command->cmd, "unset"))
		cmd_unset(command);
	else if (!ft_strcmp(command->cmd, "cd"))
		cmd_cd(command);
	else if (!ft_strcmp(command->cmd, "exit"))
		cmd_exit(command);
	else
		cmd_execve(command);
	return ;
}

static void		execute_job(t_table *table, t_job *job)
{
	int		pidx;

	pidx = 0;
	while (job)
	{
		dup_pipe(job, pidx);
		if (!execute_redirection(table, job))
		{
			job = job->next;
			continue;
		}
		execute_command(&job->command);
		pidx++;
		job = job->next;
	}
	return ;
}

void			execute_table(t_table *table)
{
	int		status;

	g_maxfd = 2;
	if (!table || !table->job_list || !table->job_list->command.cmd)
		return ;
	save_standard_fd(table);
	g_pipes = make_pipes(table->job_list);
	if (table->sep_type == AND && g_res == 0)
		execute_job(table, table->job_list);
	else if (table->sep_type == OR && g_res != 0)
		execute_job(table, table->job_list);
	else if (table->sep_type == SEMI || table->sep_type == NONE)
		execute_job(table, table->job_list);
	while (wait(&status) > 0)
		g_res = WEXITSTATUS(status);
	restore_standard_fd(table);
	close_fd_and_pipes();
	return ;
}
