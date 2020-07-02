#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void		set_redir_file(char **tokens, t_lexer *lexer, \
			t_table *table)
{
	t_redir		*redir;

	printf("SET_REDIR_FILE\n");
	redir = get_last_redir(table);
	redir->arg = ft_strdup(tokens[lexer->idx]);
	return ;
}

void		set_command_cmd(char **tokens, t_lexer *lexer, \
			t_parser *parser, t_table *table)
{
	t_job		*job;

	printf("SET_COMMAND_CMD\n");
	job = get_last_job(table);
	job->command.cmd = ft_strdup(tokens[lexer->idx]);
	parser->command = TRUE;
	return ;
}

void		set_command_arg(char **tokens, t_lexer *lexer, \
			t_table *table)
{
	t_job		*job;
	char		***arg;

	printf("SET_COMMAND_ARG\n");
	job = get_last_job(table);
	arg = &job->command.arg_list;
		ft_realloc_doublestr(arg, tokens[lexer->idx]);
	return ;
}
