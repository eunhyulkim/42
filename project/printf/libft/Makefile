NAME =	libft.a
INCLUDES = -I./includes/
CC		= gcc
RM		= rm -f
CFLAGS = -g -Wall -Wextra -Werror

MAIN_FILES =	ft_memset ft_strlen ft_isnum ft_isset ft_iszero \
				ft_putchar_fd ft_putstr_fd ft_putnbr_fd \
				ft_atoll ft_moveatoll ft_lltoa ft_ultoa ft_ftoa ft_etoa ft_lftovna \
				ft_strchr ft_strrchr ft_strnstr ft_strdup ft_strfreedup \
				ft_strinsert ft_strremove ft_strmjoin \
				ft_abs ft_digit ft_swapc ft_pow ft_trans_base \
				ft_ustrmjoin ft_ustrlen ft_ustrdup ft_ustrremove ft_round

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

SRCS = $(addprefix srcs/, $(addsuffix .c, $(MAIN_FILES)))
OBJS = $(addsuffix .o, $(MAIN_FILES))

all:	${NAME}

$(NAME): ${OBJS}
	@echo "$(RESET)Making your libft.a"
	@ar rcs ${NAME} ${OBJS}

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

clean:
	@echo "$(RESET)Cleaning your libft .o files"
	@${RM} ${OBJS}

fclean:	clean
	@echo "$(RESET)Removing ${NAME}"
	@${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
