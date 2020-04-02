NAME = factorization
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS_PATH = factorization
SRCS = $(addsuffix .c, $(SRCS_PATH))
OBJS = $(addsuffix .o, $(SRCS_PATH))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): ${OBJS}
	@echo "$(GREEN)factorization START"
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)DONE"

${OBJS}:
	@${CC} ${CFLAGS} -c ${SRCS}

clean:
	@echo "$(RED)Cleaning your .o files"
	@${RM} ${OBJS}
	@echo "$(RED)DONE"

fclean: clean
	@echo "$(RED)Cleaning your .o files"
	@${RM} ${OBJS}
	@echo "$(RED)Removing factorization"
	@${RM} ${NAME}
	@echo "$(RED)DONE"

re: fclean all