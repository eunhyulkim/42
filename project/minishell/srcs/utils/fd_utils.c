/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:48:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 23:45:29 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_fd(t_redir *redir)
{
	int		fd;
	char	*temp_path;

	fd = -1;
	if (redir->error)
		return (-2);
	if (!(ft_strcmp(redir->sign, ">")))
		fd = open(redir->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!(ft_strcmp(redir->sign, ">>")))
		fd = open(redir->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!(ft_strcmp(redir->sign, "<")))
		fd = open(redir->arg, O_RDWR);
	else if (!(ft_strcmp(redir->sign, "<<")))
	{
		temp_path = get_config_path(TEMP_PATH);
		fd = open(temp_path, O_RDWR);
		ft_free_str(&temp_path);
	}
	if (fd > g_maxfd)
		g_maxfd = fd;
	return (fd);
}

void	save_standard_fd(t_table *table)
{
	table->fd[0] = dup(0);
	table->fd[1] = dup(1);
	table->fd[2] = dup(2);
}

void	redirect_stdout_fd(t_table *table)
{
	dup2(table->fd[1], 1);
	dup2(table->fd[2], 2);
}

void	restore_standard_fd(t_table *table)
{
	dup2(table->fd[0], 0);
	dup2(table->fd[1], 1);
	dup2(table->fd[2], 2);
	close(table->fd[0]);
	close(table->fd[1]);
	close(table->fd[2]);
}

void	close_fd_and_pipes(void)
{
	while (g_maxfd > 2)
		close(g_maxfd--);
	ft_free_intptr(&g_pipes);
}
