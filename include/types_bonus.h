/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:55:27 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 18:13:03 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

typedef int			t_bool;

/*
** tokenizer.c
*/
typedef struct			s_tokenizer
{
	int					idx;
	int					qidx;
	int					start;
	int					prev;
	char				quote;
}						t_tokenizer;

/*
** lexer.c
*/
typedef struct			s_lexer
{
	int					len;
	int					idx;
	char				type;
	char				**seqs;
	char				**format;
	int					i;
	int					j;
	int					res;
}						t_lexer;

/*
** parser.c
*/
typedef struct			s_parser
{
	int					command;
	int					fd;
}						t_parser;

/*
** table structure with almost files
*/
typedef struct			s_redir
{
	char				*sign;
	int					fd;
	int					error;
	char				*arg;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_command
{
	char				*cmd;
	char				**arg_list;
	int					idx;
}						t_command;

typedef struct			s_job
{
	struct s_command	command;
	struct s_redir		*redir_list;
	struct s_job		*next;
}						t_job;

typedef struct			s_table
{
	struct s_job		*job_list;
	int					sep_type;
	int					fd[3];
	struct s_table		*next;
}						t_table;

/*
** termcaps bonus
*/

typedef struct			s_dlist
{
	void				*content;
	size_t				content_size;
	struct s_dlist		*next;
	struct s_dlist		*prev;
}						t_dlist;

typedef struct			s_winsz
{
	size_t				row;
	size_t				col;
}						t_winsz;

typedef struct			s_line
{
	t_dlist				*hist;
	size_t				cursor;
	size_t				length;
	size_t				hist_depth;
	size_t				hist_size;
	t_winsz				winsz;
	t_winsz				start;
	char				cmd[MAX_CMD_LEN];
}						t_line;

typedef struct			s_keymatch
{
	char				*key_code;
	int					key_ret;
}						t_keymatch;

typedef struct			s_keymove
{
	int					key;
	void				(*p)(t_line *line);
}						t_keymove;

struct					s_keyhist
{
	int					key;
	void				(*p)(t_line *line, t_dlist **hist);
};
#endif
