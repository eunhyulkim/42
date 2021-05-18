/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:48:43 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 10:48:49 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_job(t_job *job)
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

int				*make_pipes(t_job *job)
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

void			dup_pipe(t_job *job, int pidx)
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
