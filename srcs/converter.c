#include "minishell.h"

static void		convert_env(char **ret, char *str, int *i)
{
	char	*name;
	char	*val;
	bool	bracket;
	int		j;
	char	end;

	j = *i + 1;
	if (!str[j])
		return ;
	bracket = (str[j] == '{') ? TRUE : FALSE;
	j += (bracket) ? 1 : 0;
	end = (bracket) ? '}' : ' ';
	name = 0;
	while (str[j] && str[j] != end && !ft_isset(str[j], "\'\""))
		ft_realloc(&name, str[j++]);
	if (!str[j] || end == ' ')
		j--;
	val = get_env(name);
	*i = 0;
	while (val && val[*i])
		ft_realloc(ret, val[(*i)++]);
	ft_free(name);
	*i = j;
	return ;
}

static void		convert(char **src)
{
	int		i;
	int		opened;
	char	*str;
	char	*ret;

	i = 0;
	opened = 0;
	str = *src;
	if (!(ret = (char *)ft_calloc(sizeof(char), 1)))
		return ;
	while (str[i])
	{
		if (!opened && ft_isset(str[i], "\'\""))
			opened = str[i];
		else if (opened && opened == str[i])
			opened = 0;
		else if (opened != '\'' && str[i] == '$' \
			&& str[i + 1] && !ft_isset(str[i + 1], " \'\""))
				convert_env(&ret, str, &i);
		else
			ft_realloc(&ret, str[i]);
		i++;
	}
	free(str);
	*src = ret;
}

static void		convert_job(t_job *job)
{
	int			i;
	t_redir		*redir;

	if (job->command.cmd)
		convert(&job->command.cmd);
	if (job->command.arg_list)
	{
		i = 0;
		while (job->command.arg_list[i])
			convert(&job->command.arg_list[i++]);
	}
	if (job->redir_list)
	{
		redir = job->redir_list;
		while (redir)
		{
			if (redir->sign)
				convert(&redir->sign);
			if (redir->arg)
				convert(&redir->arg);
			redir = redir->next;
		}
	}
	return ;
}

void			converter(t_table *table)
{
	t_job	*job;

	while (table)
	{
		job = table->job_list;
		while (job)
		{
			convert_job(job);
			job = job->next;
		}
		table = table->next;
	}
	return ;
}
