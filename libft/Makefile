NAME =	libft.a
INCLUDES = -I ../include/
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

MAIN_FILES = ft_strchr ft_strlen ft_split ft_strdup ft_dup_doublestr \
			 ft_memset ft_calloc ft_len_doublestr ft_free_doublestr ft_strnstr

SRCS_PATH = $(MAIN_FILES)
SRCS = $(addprefix srcs/, $(addsuffix .c, $(SRCS_PATH)))
OBJS = $(addsuffix .o, $(MAIN_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all:	$(NAME)

$(NAME): ${OBJS}
	@echo "$(RESET)Making your libft.a$(RESET)"
	@ar rcs ${NAME} ${OBJS}

${OBJS}:
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

clean:
	@echo "$(RESET)Cleaning your libft .o files$(RESET)"
	@${RM} ${OBJS}

fclean:	clean
	@${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re bonus
