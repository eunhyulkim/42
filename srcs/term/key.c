#include "minishell.h"

static int	match_key(char *key_str, int i)
{
	static t_keymatch	key_couple[11] = {
		{KEY_CODE_UP, KEY_UP},
		{KEY_CODE_DO, KEY_DOWN},
		{KEY_CODE_RI, KEY_RIGHT},
		{KEY_CODE_LE, KEY_LEFT},
		{KEY_CODE_DEL, KEY_DC},
		{KEY_CODE_HOME, KEY_HOME},
		{KEY_CODE_END, KEY_END},
		{KEY_CODE_SRI, KEY_SRIGHT},
		{KEY_CODE_SLE, KEY_SLEFT},
		{KEY_CODE_SUP, KEY_SPREVIOUS},
		{KEY_CODE_SDO, KEY_SNEXT}
	};
	i = 0;
	while (i < 11)
	{
		if (i < 7 && !ft_memcmp(key_couple[i].key_code, key_str, MAX_KEY_LEN))
			return (key_couple[i].key_ret);
		if (i >= 7 && i < 9 && !ft_memcmp(key_couple[i].key_code, key_str, MAX_KEY_LEN - 2))
			return (key_couple[i].key_ret);
		if (i >= 9 && i < 11 && !ft_memcmp(key_couple[i].key_code, key_str, MAX_KEY_LEN + 2))
			return (key_couple[i].key_ret);
		i++;
	}
	return (key_str[0]);
}

int			get_key(void)
{
	char	*key_str;
	int		key_pressed;

	if (!(key_str = ft_calloc(sizeof(char), 7)))
		return (-1);
	if (!key_str)
		return (-1);
	read(0, key_str, 1);
	if (*key_str == '\x1b')
		read(0, key_str + 1, 1);
	if (*(key_str + 1) == '\x5b')
		read(0, key_str + 2, 2);
	if (*(key_str + 2) == '\x31' && *(key_str + 3) == '\x3b')
		read(0, key_str + 4, 2);
	int i = 0;
	dprintf(g_fd, "INPUT_KEY: ");
	while (key_str[i])
		dprintf(g_fd, "[%d]", key_str[i++]);

	key_pressed = match_key(key_str, 0);
	dprintf(g_fd, "KEY_PRESSED: [%d]\n", key_pressed);
	free(key_str);
	return (key_pressed);
}
