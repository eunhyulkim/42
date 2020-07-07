/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 05:44:00 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/21 01:01:53 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

static char		**get_args(t_command *command)
{
	char	**args;
	char	*filename;
	int		idx;

	args = 0;
	if (!(filename = strrchr(command->cmd, '/')))
		filename = ft_strdup(filename);
	else
	filename = ft_strdup(command->cmd);
	ft_realloc_doublestr(&args, filename);
	idx = 0;
	while (command->arg_list[idx])
		ft_realloc_doublestr(&args, command->arg_list[idx++]);
	return (args);
}

static void     run_exec(t_command *command)
{
    pid_t   pid;
    char    *path;
    char    **args;

    path = command->cmd;
    args = get_args(command);
    pid = fork();
    // signal(SIGINT, proc_signal_handler);
    if (pid == 0)
        execve(path, args, g_env);
    else if (pid < 0)
    {
        ft_putendl_fd("Fork failed for new process", 1);
        return ;
    }
    wait(&pid);
    return ;
}

static char     *check_bins(char *cmd)
{
    char            **path;
    char            *bin_path;
    struct stat     stat;
    int             idx;

    path = ft_split(get_env("PATH"), ':');
    idx = 0;
    while (path[idx])
    {
        if (ft_startswith(cmd, path[idx]))
            bin_path = ft_strdup(cmd);
        else
            bin_path = ft_strjoin(path[idx], cmd);
        if (lstat(bin_path, &stat) != -1)
            free(bin_path);
        else if (stat.st_mode & S_IFREG)
        {
            ft_free_doublestr(path);
            return (bin_path);
        }
    }
    ft_free_doublestr(path);
    return (0);
}

static void		run_exec_bin(char *path, t_command *command)
{
    struct stat     stat;

    lstat(path, &stat);
    ft_free(command->cmd);
    command->cmd = path;
    if (stat.st_mode & S_IXUSR)
    {
        ft_free(command->cmd);
        command->cmd = path;
        return (run_exec(command));
    }
    ft_putstr_fd("mongshell: permission denied: ", 1);
    ft_putendl_fd(path, 1);
    return ;
}

void            cmd_exec(t_command *command)
{
    struct stat     stat;
    char            *path;

    if ((path = check_bins(command->cmd)))
        return (run_exec_bin(path, command));
    if (lstat(command->cmd, &stat) != -1)
    {
        if (stat.st_mode & S_IFDIR)
            return (cmd_cd(command));
        else if (stat.st_mode & S_IXUSR)
            return (run_exec(command));
    }
    ft_putstr_fd("mongshell: command not found: ", 1);
    ft_putendl_fd(command->cmd, 1);
    return ;
}
