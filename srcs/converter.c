#include "minishell.h"

static void		convert_res(char **ret, char *str, int *i, int first)
{
	char	*val;
	int		j;

	val = (first) ? ft_itoa(g_res) : ft_strdup("0");
	j = (str[*i + 1] == '{') ? *i + 3 : *i + 1;
	*i = 0;
	while (val && val[*i])
		ft_realloc(ret, val[(*i)++]);
	*i = j;
	ft_free(val);
	return ;
}

static void		convert_env(char **ret, char *str, int *i, int first)
{
	char	*name;
	char	*val;
	bool	bracket;
	int		j;
	char	end;

	if (str[*i + 1] == '?' || (str[*i + 1] == '{' && str[*i + 2] == '?'))
		return (convert_res(ret, str, i, first));
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
}

static void		convert(char **src, int first)
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
				convert_env(&ret, str, &i, first);
		else
			ft_realloc(&ret, str[i]);
		i++;
	}
	free(str);
	*src = ret;
}

static void		convert_job(t_job *job, int first)
{
	int			i;
	t_redir		*redir;

	if (job->command.cmd)
		convert(&job->command.cmd, first);
	i = 0;
	if (job->command.arg_list)
		while (job->command.arg_list[i])
			convert(&job->command.arg_list[i++], first);
	if (!job->redir_list)
		return ;
	redir = job->redir_list;
	while (redir)
	{
		if (!ft_strcmp(redir->sign, "<<"))
			convert_heredoc(redir);
		else
		{
			if (redir->sign)
				convert(&redir->sign, first);
			if (redir->arg)
				convert(&redir->arg, first);
		}
		redir = redir->next;
	}
}

void			converter(t_table *table)
{
	t_job	*job;
	int		first;

	first = 1;
	job = table->job_list;
	while (job)
	{
		convert_job(job, first);
		job = job->next;
		first = 0;
	}
	return ;
}
