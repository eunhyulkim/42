NAME = webserv
PROXY_NAME = proxy
CC = clang++
RM = rm -rf
INCLUDES = -Iincludes/
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_FILES = libft base64 Config Connection HtmlWriter \
			 Config Location Request Response Server \
			 ServerManager main

SRCS = $(addprefix srcs/, $(addsuffix .cpp, $(SRCS_FILES)))
OBJS = $(addsuffix .o, $(SRCS_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

${NAME}: ${OBJS}
	@echo "$(GREEN)$(NAME) START$(RESET)"
	@echo "$(RESET)Compiling ${NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} -o ${NAME}
	@echo "$(GREEN)DONE$(RESET)"

clean:
	@echo "$(RESET)Cleaning your .o files$(RESET)"
	@${RM} $(OBJS)
	@echo "$(RED)clean DONE$(RESET)"

fclean: clean
	@echo "$(RESET)Removing $(NAME)"
	@${RM} $(NAME)
	@echo "$(RED)fclean DONE$(RESET)"

re: fclean all proxy

.PHONY:	all clean fclean re bonus
