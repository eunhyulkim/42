/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:14:21 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/14 17:01:08 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_BONUS_H
# define TERMCAPS_BONUS_H

# include <sys/uio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>

char		*line_editing(char **cmd_line);
void		raw_term_mode(void);
void		default_term_mode(void);
t_dlist		*retrieve_history(void);
void		get_cursor_start_pos(t_line *line);

void		input_loop(t_line *line);
int			get_key(void);
int			ft_getwinsz(t_winsz *winsz);
void		match_move(int key_pressed, t_line *line);
void		match_hist(int key_pressed, t_line *line);
void		old_hist_entry(t_line *line, t_dlist **hist);
void		new_hist_entry(t_line *line, t_dlist **hist);
void		append_history(char *entry);

void		set_curpos(t_line *line);
void		cursor_to_end(t_line *line);
void		cursor_to_home(t_line *line);
void		cursor_to_left(t_line *line);
void		cursor_to_right(t_line *line);

void		goto_next_word(t_line *line);
void		goto_prev_word(t_line *line);
void		goto_next_line(t_line *line);
void		goto_prev_line(t_line *line);

void		insert_char(t_line *line, int key);
void		delete_char(t_line *line, int key);
int			tc_putc(int c);

void		ft_dlstadd(t_dlist **head, t_dlist *new);
t_dlist		*ft_dlstnew(void const *content, size_t content_size);
size_t		ft_dlstsize(t_dlist *lst);
void		ft_dlstremovenode(t_dlist **head);
void		ft_dlstdelstr(t_dlist **lst);

#endif
