#include "minishell.h"

int		tc_putc(int c)
{
	return (write(0, &c, 1));
}
