NAME =	libasm.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NA = nasm
NFLAGS = -f macho64
RM = rm -rf

TNAME = test
TFILE = main.c
TBNAME = test_bonus
TBFILE = main_bonus.c
TFLAGS = -L. -lasm -o

MAIN_FILES = read write strlen strcmp strcpy strdup
BONUS_FILES = atoi_base list_push_front list_remove_if list_size list_sort

SRCS = $(addprefix ft_, $(addsuffix .s, $(MAIN_FILES)))
OBJS = $(addprefix ft_, $(addsuffix .o, $(MAIN_FILES)))
BONUS_SRCS = $(addprefix ft_, $(addsuffix _bonus.s, $(BONUS_FILES)))
BONUS_OBJS = $(addprefix ft_, $(addsuffix _bonus.o, $(BONUS_FILES)))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

%.o: %.s
	@${NA} ${NFLAGS} $<

all:	${NAME}

${NAME}: ${OBJS}
	@echo "$(RESET)Making your libasm.a$(RESET)"
	@ar rcs ${NAME} ${OBJS}
	@echo "$(GREEN)DONE$(RESET)"

clean:
	@echo "$(RESET)Cleaning your libasm .o files$(RESET)"
	@${RM} ${OBJS} ${BONUS_OBJS} ${TNAME} ${TBNAME}
	@echo "$(RED)DONE$(RESET)"

fclean:	clean
	@echo "$(RESET)Cleaning your execute files$(RESET)"
	@${RM} ${NAME}
	@echo "$(RED)DONE$(RESET)"

re:	fclean all

bonus: ${OBJS} ${BONUS_OBJS}
	@echo "$(RESET)Making your libasm.a with bonus$(RESET)"
	@ar rcs ${NAME} ${OBJS} ${BONUS_OBJS}
	@echo "$(GREEN)DONE$(RESET)"

test: ${NAME}
	@${CC} ${CFLAGS} ${TFLAGS} ${TNAME} ${TFILE}
	@./${TNAME}

bonus_test: bonus
	@${CC} ${CFLAGS} ${TFLAGS} ${TBNAME} ${TBFILE}
	@./${TBNAME}

.PHONY:	all clean fclean re bonus test test_bonus
