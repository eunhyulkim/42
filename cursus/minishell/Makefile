NAME = mongshell
BNAME = mongshell_bonus
INCLUDES = -I./include/
CC = gcc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror

LIB_DIR = libft/
LIBLARY = libft.a
LFLAGS = -L. -lft -ltermcap

MAIN_FILES = display tokenizer lexer parser expander converter \
			 heredoc execute execve free error escaper
UTILS_FILES = parser_get_utils parser_set_utils expander_utils \
			 fd_utils pipe_utils converter_utils
BIN_FILES = cd echo env exit export pwd unset
GNL_FILES = get_next_line get_next_line_utils
TERM_FILES = cursor_move dlst_utils ft_getwinsz get_input history key \
			 pos set_term_mode tc_putc goto_move history_utils
DIFF_FILES = main signal

COMMON_PATH = $(MAIN_FILES)
COMMON_PATH += $(addprefix utils/, $(UTILS_FILES))
COMMON_PATH += $(addprefix bin/, $(BIN_FILES))
COMMON_PATH += $(addprefix get_next_line/, $(GNL_FILES))

SRCS_PATH = $(COMMON_PATH)
SRCS_PATH += $(DIFF_FILES)
SRCS = $(addprefix srcs/, $(addsuffix .c, $(SRCS_PATH)))

BSRCS_PATH = $(addsuffix _bonus, $(DIFF_FILES))
BSRCS_PATH += $(addprefix term/, $(TERM_FILES))
BSRCS = $(addprefix srcs/, $(addsuffix .c, $(BSRCS_PATH)))

COMMON_OBJS = $(addsuffix .o, $(MAIN_FILES))
COMMON_OBJS += $(addsuffix .o, $(UTILS_FILES))
COMMON_OBJS += $(addsuffix .o, $(BIN_FILES))
COMMON_OBJS += $(addsuffix .o, $(GNL_FILES))

OBJS = $(COMMON_OBJS)
OBJS += $(addsuffix .o, $(DIFF_FILES))

BOBJS = $(COMMON_OBJS)
BOBJS += $(addsuffix .o, $(TERM_FILES))
BOBJS += $(addsuffix _bonus.o, $(DIFF_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

${NAME}: ${OBJS}
	@echo "$(GREEN)MONGSHELL START$(RESET)"
	@make -C ${LIB_DIR}
	@echo "$(RESET)Copying ${LIBLARY} to root."
	@cp ${LIB_DIR}${LIBLARY} .
	@echo "$(RESET)Compiling ${NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} -o ${NAME} ${LFLAGS}
	@echo "$(GREEN)DONE$(RESET)"

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

bonus: bonus_objs
	@echo "$(GREEN)MONGSHELL_BONUS START$(RESET)"
	@make -C ${LIB_DIR}
	@echo "$(RESET)Copying ${LIBLARY} to root."
	@cp ${LIB_DIR}${LIBLARY} .
	@echo "$(RESET)Compiling ${BNAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${BOBJS} -o ${BNAME} ${LFLAGS}
	@echo "$(GREEN)DONE$(RESET)"

bonus_objs: ${OBJS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${BSRCS}

clean:
	@echo "$(RESET)Cleaning your mongshell .o files$(RESET)"
	@${RM} $(OBJS) $(BOBJS)
	@echo "Cleaning your libft files"
	@make -C libft/ fclean
	@${RM} ${LIBLARY}
	@echo "$(RED)clean DONE$(RESET)"

fclean: clean
	@echo "$(RESET)Removing mongshell"
	@${RM} $(NAME) $(BNAME)
	@echo "$(RED)fclean DONE$(RESET)"

re: fclean all

libft_test:
	@echo "$(GREEN)TEST START$(RESET)"
	@make -C libft/ test
	@echo "$(GREEN)DONE$(RESET)"

.PHONY:	all clean fclean re bonus