#include "minishell.h"
#include "lexer.h"

void		print_table(t_table *table)
{
	t_job	*job;
	t_redir	*redir;
	char	**arg;
	int		idx;

	if (!table)
		return ;
	int tno = 0;
	printf("\n%s%-10s%-6s%-8s%-16s%-25s%s\n", KCYN, "TABLE_NO", "TYPE", "JOB_NO", \
	"CMD", "ARG", "REDIRECT");
	while (table)
	{
		tno++;
		job = table->job_list;
		int jno = 1;
		while (job)
		{
			printf("%s%-10d", KNRM, tno);
			if (!table->sep_type)
				printf("%-6s", "START");
			else if (table->sep_type == AND)
				printf("%-6s", "AND");
			else if (table->sep_type == OR)
				printf("%-6s", "OR");
			else if (table->sep_type == SEMI)
				printf("%-6s", "SEMI");
			printf("%-8d", jno++);
			if (job->command.cmd)
				printf("%-16s", job->command.cmd);
			else
				printf("%s%-16s%s", KYEL, "Null", KNRM);
			arg = job->command.arg_list;
			idx = 0;
			int len = 0;
			if (!arg && (len = 25))
				printf("%s%-25s%s", KYEL, "Null", KNRM);
			while (arg && arg[idx])
			{
				printf("%s,", arg[idx]);
				len += ft_strlen(arg[idx]) + 1;
				idx++;
			}
			len = 25 - len;
			while (len--)
				printf(" ");
			if (!job->redir_list)
				printf("%s%s%s\n", KYEL, "Null", KNRM);
			else
			{
				redir = job->redir_list;
				while (redir)
				{
					if (redir->sign[0] == '>')
						printf("%d", redir->fd);
					printf("%s", redir->sign);
					printf("%s,", redir->arg);
					redir = redir->next;
				}
				printf("\n");
			}
			job = job->next;
		}
		table = table->next;
	}
}
