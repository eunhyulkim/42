NAME =	libft.a
INCLUDES = -I ../include/
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

MAIN_FILES = ft_strchr ft_strlen ft_split ft_strdup ft_calloc \
			 ft_memset ft_strcat ft_strcpy ft_strjoin ft_strnew \
			 ft_strsub ft_putstr_fd ft_isspace ft_strcmp ft_strncmp \
			 ft_isalpha ft_isascii ft_isnum ft_isprint ft_isset \
			 ft_atoi ft_realloc ft_memcpy ft_itoa ft_putendl_fd \
			 ft_strrchr ft_isnumber ft_bzero ft_isdigit ft_memcmp \
			 ft_memmove ft_putchar_fd

BONUS_FILES = ft_dup_doublestr ft_len_doublestr ft_free_doublestr \
			  ft_realloc_doublestr ft_startswith ft_isformat ft_in \
			  ft_isitem ft_strreverse ft_free ft_isright_quote \
			  ft_isright_envbracket ft_sort_doublestr ft_remove_doublestr \
			  ft_strsjoin ft_isformat2 ft_mstrjoin ft_free_str ft_free_intptr

TEST_FILE = test/ft_isformat2_test.c

SRCS_PATH = $(MAIN_FILES)
SRCS_PATH += $(BONUS_FILES)
SRCS = $(addprefix srcs/, $(addsuffix .c, $(SRCS_PATH)))
OBJS = $(addsuffix .o, $(MAIN_FILES))
OBJS += $(addsuffix .o, $(BONUS_FILES))

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

test: fclean all
	@${CC} ${CFLAGS} ${INCLUDES} -lft -L. ${TEST_FILE} -o testfile
	@./testfile


.PHONY:	all clean fclean re bonus
