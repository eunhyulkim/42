NAME = eval_expr
CC = clang++
RM = rm -f
INCLUDES = -I.
CFLAGS = -Wall -Wextra -Werror

MAIN_FILES = main parse eval
CLASS_FILES = Fixed
SRCS = $(addsuffix .cpp, $(MAIN_FILES))
SRCS += $(addsuffix .class.cpp, $(CLASS_FILES))
OBJS = $(addsuffix .o, $(MAIN_FILES))
OBJS += $(addsuffix .class.o, $(CLASS_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

${NAME}: ${OBJS}
	@echo "$(GREEN)$(NAME) START$(RESET)"
	@echo "$(RESET)Compiling ${NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} -o ${NAME}
	@echo "$(GREEN)DONE$(RESET)"

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

clean:
	@echo "$(RESET)Cleaning your .o files$(RESET)"
	@${RM} $(OBJS)
	@echo "$(RED)clean DONE$(RESET)"

fclean: clean
	@echo "$(RESET)Removing $(NAME)"
	@${RM} $(NAME)
	@echo "$(RED)fclean DONE$(RESET)"

re: fclean all

test: $(NAME)
	@./$(NAME)

.PHONY:	all clean fclean re bonus
