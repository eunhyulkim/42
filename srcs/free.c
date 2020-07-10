/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:56:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 11:57:03 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_redir_list(t_redir *redir)
{
	t_redir		*temp;

	if (!redir)
		return ;
	while (redir)
	{
		if (redir->sign)
			free(redir->sign);
		if (redir->arg)
			free(redir->arg);
		temp = redir->next;
		free(redir);
		redir = temp;
	}
}

static void		free_job_list(t_job *job)
{
	t_job	*temp;

	if (!job)
		return ;
	while (job)
	{
		if (job->command.cmd)
			free(job->command.cmd);
		if (job->command.arg_list)
			ft_free_doublestr(job->command.arg_list);
		if (job->redir_list)
			free_redir_list(job->redir_list);
		temp = job->next;
		free(job);
		job = temp;
	}
}

void			free_tables(t_table *table)
{
	t_table		*temp;

	if (!table)
		return ;
	while (table)
	{
		if (table->job_list)
			free_job_list(table->job_list);
		temp = table->next;
		free(table);
		table = temp;
	}
	free(table);
	return ;
}
