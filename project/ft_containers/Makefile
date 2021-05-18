NAME = ft_containers
CC = clang++
RM = rm -rf
INCLUDES = -I./includes/
CFLAGS = -std=c++98 -Wall -Wextra -Werror

FILES = list stack vector map queue deque multimap set multiset
MAIN = main Myclass

SRCS = $(addsuffix .cpp, $(addprefix test/, $(MAIN)))
SRCS += $(addsuffix _test.cpp, $(addprefix test/, $(FILES)))

OBJS = $(addsuffix .o, $(MAIN))
OBJS += $(addsuffix _test.o, $(FILES))

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

.PHONY:	all clean fclean re bonus
