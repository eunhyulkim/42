NAME = webserv
PROXY_NAME = proxy
CC = clang++
RM = rm -rf
INCLUDES = -Iincludes/
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_FILES = base64 Request Location Response Config HtmlWriter \
			 Connection libft Worker Server ServerManager
SERVER_FILES = main
PROXY_FILES = Proxy ProxyManager proxy_main

SRCS = $(addprefix srcs/, $(addsuffix .cpp, $(SRCS_FILES)))
SSRCS = $(addprefix srcs/, $(addsuffix .cpp, $(SERVER_FILES)))
PSRCS = $(addprefix srcs/, $(addsuffix .cpp, $(PROXY_FILES)))
OBJS = $(addsuffix .o, $(SRCS_FILES))
SOBJS = $(addsuffix .o, $(SERVER_FILES))
POBJS = $(addsuffix .o, $(PROXY_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

${OBJS}: ${SRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SRCS}

${SOBJS}: ${SSRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${SSRCS}

${POBJS}: ${PSRCS}
	@${CC} ${CFLAGS} ${INCLUDES} -c ${PSRCS}

${NAME}: ${OBJS} ${SOBJS}
	@echo "$(GREEN)$(NAME) START$(RESET)"
	@echo "$(RESET)Compiling ${NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${MOBJS} -o ${NAME} -framework Python
	@echo "$(GREEN)DONE$(RESET)"

${PROXY_NAME}: ${OBJS} ${POBJS}
	@echo "$(GREEN)$(PROXY_NAME) START$(RESET)"
	@echo "$(RESET)Compiling ${PROXY_NAME} to root."
	@${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${POBJS} -o ${PROXY_NAME}
	@echo "$(GREEN)DONE$(RESET)"

clean:
	@echo "$(RESET)Cleaning your .o files$(RESET)"
	@${RM} $(OBJS) $(SOBJS) $(POBJS)
	@echo "$(RED)clean DONE$(RESET)"

fclean: clean
	@echo "$(RESET)Removing $(NAME)"
	@${RM} $(NAME) $(PROXY_NAME)
	@echo "$(RED)fclean DONE$(RESET)"

re: fclean all proxy

.PHONY:	all clean fclean re bonus
