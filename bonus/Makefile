NAME = webserv
PROXY_NAME = proxy
CC = clang++
RM = rm -rf
INCLUDES = -Iincludes/
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS_FILES = ServerManager base64 Request Location Response Config HtmlWriter \
			 Connection libft Server Worker
PROXY_FILES = ProxyBase base_proxy_test

SRCS = $(addprefix srcs/, $(addsuffix .cpp, $(SRCS_FILES)))
MSRCS = srcs/main.cpp
BSRCS = $(addprefix srcs/, $(addsuffix .cpp, $(PROXY_FILES)))
OBJS = $(addsuffix .o, $(SRCS_FILES))
MOBJS = main.o
BOBJS = $(addsuffix .o, $(PROXY_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

${BOBJS}: ${BSRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${BSRCS}

${MOBJS}: ${MSRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${MSRCS}

${NAME}: ${OBJS} ${MOBJS}
	@echo "$(GREEN)$(NAME) START$(RESET)"
	@echo "$(RESET)Compiling ${NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${MOBJS} -o ${NAME}
	@echo "$(GREEN)DONE$(RESET)"


${PROXY_NAME}: ${OBJS} ${BOBJS}
	@echo "$(GREEN)$(NAME) START$(RESET)"
	@echo "$(RESET)Compiling ${NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${BOBJS} -o ${PROXY_NAME}
	@echo "$(GREEN)DONE$(RESET)"

clean:
	@echo "$(RESET)Cleaning your .o files$(RESET)"
	@${RM} $(OBJS) $(MOBJS) $(BOBJS)
	@echo "$(RED)clean DONE$(RESET)"

fclean: clean
	@echo "$(RESET)Removing $(NAME)"
	@${RM} $(NAME) $(PROXY_NAME)
	@echo "$(RED)fclean DONE$(RESET)"

re: fclean all proxy

.PHONY:	all clean fclean re bonus
