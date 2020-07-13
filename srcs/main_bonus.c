/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:50:08 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 22:28:03 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_bool	is_empty_line(char *line)
{
	int		i;

	if (!line)
		return (TRUE);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' && !line[i + 1])
	{
		ft_free_str(&line);
		return (TRUE);
	}
	return (FALSE);
}

void			input_loop(t_line *line)
{
	int		key_pressed;

	while (42)
	{
		key_pressed = get_key();
		ft_getwinsz(&line->winsz);
		if (line->start.row + line->cursor / line->winsz.col > line->winsz.row)
			line->start.row--;
		match_move(key_pressed, line);
		match_hist(key_pressed, line);
		if (key_pressed > 31 && key_pressed < 127)
			insert_char(line, key_pressed);
		if (key_pressed == KEY_DC || key_pressed == 127)
			delete_char(line, key_pressed);
		if (key_pressed == KEY_CTRLL)
		{
			tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1) \
				, 1, &tc_putc);
			line->start.row = 1;
			set_curpos(line);
		}
		if (key_pressed == '\n')
			break ;
	}
}

char			*line_editing(char **cmd_line)
{
	t_line		line;

	raw_term_mode();
	ft_bzero(&line, sizeof(line));
	line.hist = retrieve_history();
	line.hist_size = ft_dlstsize(line.hist);
	get_cursor_start_pos(&line);
	input_loop(&line);
	cursor_to_end(&line);
	default_term_mode();
	ft_putchar_fd('\n', 1);
	append_history(line.cmd);
	ft_dlstdelstr(&line.hist);
	*cmd_line = ft_strjoin(line.cmd, "\n");
	return (*cmd_line);
}

static int		process_line(char *line)
{
	char		**tokens;
	t_table		*table;
	t_table		*first_table;

	line = escaper(line);
	tokens = tokenizer(line);
	ft_free_str(&line);
	if (!lexer(tokens) || !(table = parser(tokens)))
		return (TRUE);
	ft_free_doublestr(&tokens);
	first_table = table;
	while (table)
	{
		expander(table);
		converter(table);
		execute_table(table);
		table = table->next;
	}
	free_tables(first_table);
	return (TRUE);
}

int				main(int ac, char *av[], char **env)
{
	char	*cmd_line;

	if ((g_fd = open("config/log", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
		return (0);
	display_logo();
	init_env(ac, av, env);
	while (TRUE)
	{
		set_builtin_signal();
		display_prompt();
		cmd_line = 0;
		if (!(line_editing(&cmd_line)))
			ft_exit(cmd_line, 0);
		else if (is_empty_line(cmd_line))
			continue;
		process_line(cmd_line);
	}
	return (0);
}
