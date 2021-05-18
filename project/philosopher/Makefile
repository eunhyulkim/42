NAME = philo_one
INCLUDES = -I./includes/
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

MAIN_FILES = main parse init moniter simulation time print escape log \
			 ft_put ft_string utils
SRCS = $(addprefix philo_one_srcs/, $(addsuffix .c, $(MAIN_FILES)))
OBJS = $(addsuffix .o, $(MAIN_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

${NAME}: ${OBJS}
	@echo "$(GREEN)$(NAME) START$(RESET)"
	@echo "$(RESET)Compiling ${NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} -o ${NAME} -lpthread -L.
	@echo "$(GREEN)DONE$(RESET)"

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

clean:
	@echo "$(RESET)Cleaning your mongshell .o files$(RESET)"
	@${RM} $(OBJS)
	@echo "$(RED)clean DONE$(RESET)"

fclean: clean
	@echo "$(RESET)Removing mongshell"
	@${RM} $(NAME)
	@echo "$(RED)fclean DONE$(RESET)"

re: fclean all

libft_test:
	@echo "$(GREEN)TEST START$(RESET)"
	@make -C libft/ test
	@echo "$(GREEN)DONE$(RESET)"

.PHONY:	all clean fclean re bonus
