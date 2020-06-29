/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/28 13:42:16 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef COMMAND					4;
typedef ARGUMENT				5;
typedef PIPE					10;
typedef REDIRECT				6;
typedef FILENAME				7;
typedef COMMAND_PARSE_MASK		5;
typedef REDIRECT_PARSE_MASK		7;

typedef struct 			s_command
{
	struct s_command	*next;
}						t_command;

typedef struct 			s_redirect
{
	struct s_redirect	*next;
}						t_redirect;

typedef struct  		s_table
{
	struct s_command	*commands;
	struct s_redirect	*redirects;
	bool				has_cmd;
	bool				has_redirect;
	int					in_fd;
	int					out_fd;
}						t_table;

/*
** command [arguments] | cmd [arguments] | ... | redirects filename
*/

/*
** ERROR_CASE(has_cmd, has_redirect)
** PIPE		5	0
** ARGUMENT	10	0
** COMMAND	4	1
** REDIRECT	6		1
** FILENAME	7		0
*/

int			check_type(t_table *table, char **tokens, int idx)
{
	int		front;
	int		current;

	if (!ft_strcmp(tokens[idx], "|"))
		return (PIPE);
	front = (idx) ? check_type(table, tokens, idx - 1) : 0;
	if (ft_in)
}

int			is_syntax_error(t_table *table, char **tokens, int idx, int type)
{
	int		err;

	err = FALSE;
	if (type == COMMAND && table->has_cmd == TRUE)
		err = TRUE;
	else if ((type == PIPE || type == ARGUMENT) && table->has_cmd == FALSE)
		err = TRUE;
	else if (type == REDIRECT && table->has_redirect == TRUE)
		err = TRUE;
	else if (type == FILENAME && table->has_redirect == FALSE)
		err = TRUE;
	write(1, "syntax error near unexp")
	return (err) ? TRUE : FALSE;
}

t_table		*parser(char **tokens)
{
	int			idx;
	int			type;
	t_table		*table;

	idx = -1;
	if (!(table = (t_table *)ft_calloc(sizeof(t_table), 1)))
		return (0);
	while (tokens[++idx])
	{
		type = check_type(table, tokens, idx);
		if (is_syntax_error(table, tokens, idx, type))
			break ;
		if (type == COMMAND || type == ARGUMENT)
			register_command(table, tokens[idx], type);
		else if (type == REDIRECT || type == FILENAME)
			register_redirect(table, tokens[idx], type);
		else if (type == PIPE)
			table->has_cmd = FALSE;
	}
	return (table);
}
