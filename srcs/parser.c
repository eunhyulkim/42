/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 22:47:43 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		create_job(t_parser *parser, t_table *table)
{
	t_table		*last_table;
	t_job		*last_job;
	t_job		*new_job;

	if (!(new_job = (t_job *)ft_calloc(sizeof(t_job), 1)))
		return ;
	last_job = get_last_job(table);
	if (!last_job)
	{
		last_table = get_last_table(table);
		new_job->command.idx = 0;
		last_table->job_list = new_job;
		return ;
	}
	new_job->command.idx = last_job->command.idx + 1;
	last_job->next = new_job;
	parser->command = FALSE;
	return ;
}

static void		create_table(char **tokens, t_lexer *lexer, \
				t_parser *parser, t_table *table)
{
	t_table		*last_table;
	t_table		*new_table;

	if (lexer->type == 'Y' && token_in(tokens, lexer, NO_BACK_ARG))
		return ;
	if (!(new_table = (t_table *)ft_calloc(sizeof(t_table), 1)))
		return ;
	new_table->sep_type = lexer->type;
	last_table = get_last_table(table);
	last_table->next = new_table;
	parser->command = FALSE;
	create_job(parser, table);
	return ;
}

static void		create_redir(char **tokens, t_lexer *lexer, \
				t_parser *parser, t_table *table)
{
	t_job		*last_job;
	t_redir		*last_redir;
	t_redir		*new_redir;

	if (!(new_redir = (t_redir *)ft_calloc(sizeof(t_redir), 1)))
		return ;
	new_redir->sign = ft_strdup(tokens[lexer->idx]);
	if (parser->fd == TRUE)
		new_redir->fd = ft_atoi(tokens[lexer->idx - 1]);
	else if (ft_isset(lexer->type, "GH"))
		new_redir->fd = 1;
	else
		new_redir->fd = 0;
	parser->fd = FALSE;
	last_redir = get_last_redir(table);
	if (!last_redir)
	{
		last_job = get_last_job(table);
		last_job->redir_list = new_redir;
		return ;
	}
	last_redir->next = new_redir;
	return ;
}

static void		parse(char **tokens, t_lexer *lexer, t_parser *parser, \
				t_table *table)
{
	if (ft_isset(lexer->type, "SF"))
		return ;
	if (ft_isset(lexer->type, "YOA") && !token_in(tokens, lexer, NO_BACK_ARG))
		create_table(tokens, lexer, parser, table);
	else if (ft_isset(lexer->type, "P"))
		create_job(parser, table);
	else if (ft_isset(lexer->type, "GHLM"))
		create_redir(tokens, lexer, parser, table);
	else if (ft_isset(lexer->type, "NC"))
	{
		if (lexer->type == 'N' && token_in(tokens, lexer, BACK_X_GREAT))
			parser->fd = TRUE;
		else if (token_in(tokens, lexer, FRONT_REDIR))
			set_redir_file(tokens, lexer, table);
		else if (parser->command)
			set_command_arg(tokens, lexer, table);
		else
			set_command_cmd(tokens, lexer, parser, table);
	}
	return ;
}

t_table			*parser(char **tokens)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_table		*table;

	if (!(lexer = (t_lexer *)ft_calloc(sizeof(t_lexer), 1)))
		return (0);
	if (!(parser = (t_parser *)ft_calloc(sizeof(t_parser), 1)))
		return (0);
	if (!(table = (t_table *)ft_calloc(sizeof(t_table), 1)))
		return (0);
	create_job(parser, table);
	lexer->len = ft_len_doublestr(tokens);
	lexer->idx = 0;
	while (tokens[lexer->idx])
	{
		lexer->type = type(tokens, lexer->idx);
		parse(tokens, lexer, parser, table);
		lexer->idx++;
	}
	ft_free(lexer);
	ft_free(parser);
	return (table);
}
