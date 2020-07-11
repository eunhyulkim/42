/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:56:13 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 20:56:29 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		expand_command(t_command *command)
{
	char	**entries;

	if (!(entries = get_entries(command->cmd)))
		return ;
	ft_free(command->cmd);
	command->cmd = ft_strdup(entries[0]);
	ft_free_doublestr(entries);
	return ;
}

static void		expand_argument(t_command *command)
{
	int		i;
	int		j;
	char	**entries;
	char	**new_args;

	i = 0;
	entries = 0;
	new_args = 0;
	while (command->arg_list[i])
	{
		if ((entries = get_entries(command->arg_list[i])))
		{
			j = 0;
			while (entries[j])
				ft_realloc_doublestr(&new_args, entries[j++]);
		}
		ft_free_doublestr(entries);
		entries = 0;
		i++;
	}
	if (!new_args)
		return ;
	ft_free_doublestr(command->arg_list);
	command->arg_list = new_args;
	return ;
}

static void		expand_redirection(t_redir *redir)
{
	char	**entries;

	if (!(entries = get_entries(redir->arg)))
		return ;
	if (ft_len_doublestr(entries) > 1)
		redir->error = TRUE;
	else
	{
		ft_free(redir->arg);
		redir->arg = ft_strdup(entries[0]);
	}
	ft_free_doublestr(entries);
	return ;
}

static void		expand_job(t_job *job)
{
	t_redir		*redir;
	t_command	*command;

	command = &job->command;
	if (command)
		expand_command(command);
	if (command->arg_list)
		expand_argument(command);
	redir = job->redir_list;
	while (redir)
	{
		if (ft_strcmp(redir->sign, "<<") && redir->arg)
			expand_redirection(redir);
		redir = redir->next;
	}
	return ;
}

void			expander(t_table *table)
{
	t_job	*job;

	job = table->job_list;
	while (job)
	{
		expand_job(job);
		job = job->next;
	}
	return ;
}
