NAME = webserv
CC = clang++
RM = rm -rf
INCLUDES = -Iincludes/
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_FILES = ServerManager base64 Request Location Response Config HtmlWriter \
			 Connection libft main Server ProxyBase

SRCS += $(addprefix srcs/, $(addsuffix .cpp, $(SRCS_FILES)))
OBJS += $(addsuffix .o, $(SRCS_FILES))

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
