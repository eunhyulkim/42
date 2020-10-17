# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunhkim, Juejeong, Yopark            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 21:55:32 by eunhkim           #+#    #+#              #
#    Updated: 2020/10/17 21:55:37 by eunhkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************************** COLOR *********************************** #

# Basic
_END		=	\e[0m
_BOLD		=	\e[1m
_UNDER		=	\e[4m
_REV		=	\e[7m
_BACK		=	\033[2K\r

# Colors
_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m
_PURPLE		=	\e[35m
_CYAN		=	\e[36m
_WHITE		=	\e[37m

# Inverted
_IGREY		=	\e[40m
_IRED		=	\e[41m
_IGREEN		=	\e[42m
_IYELLOW	=	\e[43m
_IBLUE		=	\e[44m
_IPURPLE	=	\e[45m
_ICYAN		=	\e[46m
_IWHITE		=	\e[47m

# ******************************* SET VARIABLE ******************************* #

# Command
RM			=	rm -rf
MKDIR		=	mkdir

# Compile
CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	webserv

# Directories
DIR_HEADERS	=	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./objs/

# Files
GENERAL		=	libft \
				base64 \
				Config \
				Connection \
				HtmlWriter \
				Location \
				Request \
				Response \
				Server \
				ServerManager \
				main
SRC			=	$(GENERAL)

SRCS		=	$(addprefix $(DIR_SRCS), $(addsuffix .cpp, $(SRC)))
OBJS		=	$(addprefix $(DIR_OBJS), $(addsuffix .o, $(SRC)))

# Resources
CONFIG		=	config/default.conf

# ********************************* COMMAND ********************************** #

all:			$(NAME) $(CONFIG)

$(DIR_OBJS):
				@$(MKDIR) $(DIR_OBJS)

$(OBJS):		| $(DIR_OBJS)

${NAME}: ${OBJS}
				@printf "$(_BACK)All $(_BOLD)object files$(_END) compiled into '$(_YELLOW)$(_BOLD)$(DIR_OBJS)$(_END)'✅\n"
				@${CC} ${CFLAGS} -I ${DIR_HEADERS} ${OBJS} -o ${NAME}
				@printf "Executable '$(_GREEN)$(_BOLD)$(NAME)$(_END)' program created. go!👻\n"

$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
				@$(CC) $(CFLAGS) -I$(DIR_HEADERS) -c $< -o $@
				@printf "$(_BACK) $(_YELLOW)Compiling $(_BOLD)$< $(_END)⌛"

clean:
	@printf "Removing $(_BOLD)object files$(_END) in '$(_YELLOW)$(_BOLD)$(DIR_OBJS)$(_END)'⌛"
	@$(RM) $(OBJS)
	@printf "$(_BACK)All $(_BOLD)object files$(_END) removed in '$(_YELLOW)$(_BOLD)$(DIR_OBJS)$(_END)'✅\n"

fclean: clean
	@printf "Removing $(_BOLD)executable prgoram '$(_RED)$(NAME)$(_END)'⌛"
	@${RM} $(NAME)
	@printf "$(_BACK)$(_BOLD)executable prgoram '$(_RED)$(_BOLD)$(NAME)$(_END)' removed⌛\n"

re: fclean all

.PHONY:	all clean fclean re bonus
