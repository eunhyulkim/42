/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/01 02:45:18 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

static void		parse_number(char **tokens, t_lexer *lexer, \
				t_parser *parser, t_table *table)
{
	if (token_in(tokens, lex, "N:"X_BACK_REDIR))
		return ; // input_fd
	else if (token_in(tokens, lex, "N:"FRONT_EMP_REDIR))
		set_redir_outfd();
	else if (token_in(tokens, lex, "N:"FRONT_REDIR))
		set_redir_outfile();
	else if (parser->command)
		set_cmd_argument();
	else
		set_cmd_command();
}

static void		parse_string(char **tokens, t_lexer *lexer, \
				t_parser *parser, t_table *table)
{
	if (token_in(tokens, lex, "C:"FRONT_REDIR))
		set_redir_outfile();
	else if (parser->command)
		set_cmd_argument();
	else
		set_cmd_command();
}

static void		parse_emper(char **tokens, t_lexer *lexer, \
				t_parser *parser, t_table *table)
{

}

static void		parse(char **tokens, t_lexer *lexer, t_parser *parser, \
				t_table *table)
{
	if (ft_isset(lexer->type, "SF")) // SPCAE + NEWLINE
		return ;
	if (ft_isset(lexer->type, "GHLM")) // (D)GREAT, (D)LESS
		create_redir(tokens, lexer, parser, table);
	else if (ft_isset(lexer->type, "OAY")) // OR,AND,SEMI
		create_table(tokens, lexer, parser, table);
	else if (lexer->type == PIPE)
		create_command(tokens, lexer, parser, table);
	else if (lexer->type == NUMBER)
		parse_number(tokens, lexer, parser, table);
	else if (lexer->type == STRING)
		parse_string(tokens, lexer, parser, table);
	else if (lexer->type == EMPER)
		parse_emper(tokens, lexer, parser, table);
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
