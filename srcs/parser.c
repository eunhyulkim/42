/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/02 15:00:06 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

static void		create_table(char **tokens, t_lexer *lexer, t_parser *parser,\
				t_table *table)
{
	t_table		*new_table;
	
	if (lexer->type == 'Y' && token_in(tokens, lexer, NO_BACK_ARG))
		return ; // semiconlonf in line end
	if (!(new_table = (t_table *)ft_calloc(sizeof(t_table), 1)))
		return (0);
	new_table->sep_state = lexer->type;
	while (table->next)
		table = table->next;
	table->next = new_table;
	parser->command = FALSE;
}

static void		create_job(parse(char **tokens, t_lexer *lexer, \
				t_parser *parser, t_table *table)
{
	t_job		*job_list;
	
	while (table->next)
		table = table->next;
	job_list = table->job_list;
	if (!job_list)
		
	while (job_list->next)
		job_list = job_list->next;	
	while (table->job_list->next)
	
}

static void		create_redir(parse(char **tokens, t_lexer *lexer, \
				t_parser *parser, t_table *table)
{
	
}

static void		parse(char **tokens, t_lexer *lexer, t_parser *parser, \
				t_table *table)
{
	if (ft_isset(lexer->type, "SF")) // SPCAE + NEWLINE
		return ;
	if (ft_isset(lexer->type, "YOA")) // SEMI, OR, AND
		create_table(tokens, lexer, parser, table);
	else if (ft_isset(lexer->type, "P")) // PIPE
		create_job(tokens, lexer, parser, table);
	else if (ft_isset(lexer->type, "GHLM")) // (D)GREAT, (D)LESS
		create_redir(tokens, lexer, parser, table);
	else if (ft_isset(lexer->type, "NC"))
	{
		if (lexer->type == 'N' && token_in(tokens, lexer, X_BACK_GREAT))
			return ; // input_fd
		else if (token_in(tokens, lexer, FRONT_REDIR))
			set_redir_file();
		else if (parser->command)
			set_cmd_argument();
		else
			set_cmd_command();		
	}
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
	lexer->len = ft_len_doublestr(tokens);
	while (lexer->idx)
	{
		lexer->type = type(tokens, lexer->idx);
		parse(tokens, lexer, parser, table);
		lexer->idx++;
	}
	ft_free(lexer);
	ft_free(parser);
	return (table);
}
