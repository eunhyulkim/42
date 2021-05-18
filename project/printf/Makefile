NAME = libftprintf.a
BINCLUDES = -I./libft/includes/
LINCLUDES = -I./includes/
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LIB_DIR = libft/
LIBLARY = libft.a

CONVERSION_FILES = 	conversion_c conversion_s conversion_di conversion_u \
					conversion_xx conversion_p conversion_oo \
					conversion_n conversion_f conversion_g conversion_e \
					conversion_wc conversion_ws conversion_o conversion_arg

MAIN_FILES = 		ft_printf action arrange \
					check_flag check_sharp check_size check_type check_width \
					deliver print_content reinitialize

SRCS_PATH = $(MAIN_FILES)
SRCS_PATH += $(addprefix conversions/, $(CONVERSION_FILES))

SRCS = $(addprefix srcs/, $(addsuffix .c, $(SRCS_PATH)))
OBJS = $(addsuffix .o, $(MAIN_FILES))
OBJS += $(addsuffix .o, $(CONVERSION_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: ${NAME}

${NAME}: ${OBJS}
	@echo "$(GREEN)LIBFT START$(RESET)"
	@make -C ${LIB_DIR}
	@echo "Copying ${LIBLARY} to root."
	@cp ${LIB_DIR}${LIBLARY} .
	@mv ${LIBLARY} ${NAME}
	@echo "Making your libftprintf.a"
	@ar rcs $(NAME) ${OBJS}
	@echo "$(GREEN)DONE"

${OBJS}:
	@${CC} ${CFLAGS} ${LINCLUDES} ${BINCLUDES} -c -g ${SRCS}

clean:
	@echo "$(RESET)Cleaning your ft_printf .o files"
	@make -C libft/ fclean
	@${RM} $(OBJS)
	@echo "$(RED)clean DONE"

fclean: clean
	@echo "$(RESET)Removing ${NAME}"
	@${RM} $(NAME)
	@echo "$(RED)DONE"

bonus: fclean all

re: fclean all
