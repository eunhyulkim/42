#include "minishell.h"

int		ft_getwinsz(t_winsz *winsz)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w))
		return (1);
	winsz->col = w.ws_col;
	winsz->row = w.ws_row;
	return (0);
}
