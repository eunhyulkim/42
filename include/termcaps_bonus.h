#ifndef TERMCAPS_BONUS_H
# define TERMCAPS_BONUS_H

# include <sys/uio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>

# define MAX_KEY_LEN 4

# define KEY_CODE_UP "\x1b\x5b\x41\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0"

# define KEY_CODE_DEL "\x1b\x5b\x33\x7e"

# define KEY_CODE_HOME "\x1b\x5b\x48\0"
# define KEY_CODE_END "\x1b\x5b\x46\0"

# define KEY_CODE_SUP "\x1b\x5b\x31\x3b\x35\x41"
# define KEY_CODE_SDO "\x1b\x5b\x31\x3b\x35\x42"
# define KEY_CODE_SRI "\x1b\x66"
# define KEY_CODE_SLE "\x1b\x62"

# define KEY_CTRLL 12

char		*line_editing(char **cmd_line, t_line *line);
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
t_dlist		*ft_dlstgethead(t_dlist *dlst);

#endif
