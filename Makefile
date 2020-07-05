NAME = mongshell
INCLUDES = -I./include/
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

LIB_DIR = libft/
LIBLARY = libft.a

MAIN = test/execute_single_job_test
MAIN_FILES = display tokenizer lexer parser parser_get_utils \
			 parser_set_utils free converter debug execute
BIN_FILES = env cmd_echo
GNL_FILES = get_next_line get_next_line_utils

MAIN_PATH = $(addsuffix .c, $(MAIN))
SRCS_PATH += $(MAIN_FILES)
SRCS_PATH += $(addprefix bin/, $(BIN_FILES))
SRCS_PATH += $(addprefix get_next_line/, $(GNL_FILES))
SRCS = $(addprefix srcs/, $(addsuffix .c, $(SRCS_PATH)))

OBJS += $(addsuffix .o, $(MAIN_FILES))
OBJS += $(addsuffix .o, $(BIN_FILES))
OBJS += $(addsuffix .o, $(GNL_FILES))

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
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${MAIN_PATH} -o ${NAME} -lft -L.
	@echo "$(GREEN)DONE"

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

clean:
	@echo "$(RESET)Cleaning your mongshell .o files$(RESET)"
	@${RM} $(OBJS)
	@echo "Cleaning your libft files"
	@make -C libft/ fclean
	@${RM} ${LIBLARY}
	@echo "$(RED)clean DONE"

fclean: clean
	@echo "$(RESET)Removing mongshell"
	@${RM} $(NAME)
	@echo "$(RED)fclean DONE"

re: fclean ${OBJS} \
	all

libft_test:
	@echo "$(GREEN)TEST START$(RESET)"
	@make -C libft/ test
	@echo "$(GREEN)DONE"

.PHONY:	all clean fclean re bonus
