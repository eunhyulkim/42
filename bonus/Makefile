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
PFLAGS		=	-framework Python
NAME		=	webserv_bonus
PROXY		=	proxy

# Directories
DIR_HEADERS	=	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./objs/

# Files
COMMON_FILE	=	libft \
				base64 \
				Config \
				Connection \
				HtmlWriter \
				Location \
				Request \
				Response \
				Server \
				ServerManager \
				Worker
SERVER_FILE	=	main
PROXY_FILE	=	Proxy ProxyManager proxy_main

COMMON_SRCS	=	$(addprefix $(DIR_SRCS), $(addsuffix .cpp, $(COMMON_FILE)))
COMMON_OBJS	=	$(addprefix $(DIR_OBJS), $(addsuffix .o, $(COMMON_FILE)))
SERVER_SRCS	=	$(addprefix $(DIR_SRCS), $(addsuffix .cpp, $(SERVER_FILE)))
SERVER_OBJS	=	$(addprefix $(DIR_OBJS), $(addsuffix .o, $(SERVER_FILE)))
PROXY_SRCS	=	$(addprefix $(DIR_SRCS), $(addsuffix .cpp, $(PROXY_FILE)))
PROXY_OBJS	=	$(addprefix $(DIR_OBJS), $(addsuffix .o, $(PROXY_FILE)))

# Resources
CONFIG		=	config/bonus.conf

# ********************************* COMMAND ********************************** #

all:			$(NAME) $(CONFIG)

$(DIR_OBJS):
				@$(MKDIR) $(DIR_OBJS)

$(COMMON_OBJS):	| $(DIR_OBJS)

${NAME}:		${COMMON_OBJS} ${SERVER_OBJS}
				@printf "$(_BACK)All $(_BOLD)server object files$(_END) compiled into '$(_YELLOW)$(_BOLD)$(DIR_OBJS)$(_END)'✅\n"
				@${CC} -g ${CFLAGS} ${PFLAGS} -I ${DIR_HEADERS} ${COMMON_OBJS} ${SERVER_OBJS} -o ${NAME}
				@printf "Executable '$(_GREEN)$(_BOLD)$(NAME)$(_END)' program created. go!👻\n"

${PROXY}:		${COMMON_OBJS} ${PROXY_OBJS}
				@printf "$(_BACK)All $(_BOLD)server object files$(_END) compiled into '$(_YELLOW)$(_BOLD)$(DIR_OBJS)$(_END)'✅\n"
				@${CC} ${CFLAGS} -I ${DIR_HEADERS} ${COMMON_OBJS} ${PROXY_OBJS} -o ${PROXY}
				@printf "Executable '$(_GREEN)$(_BOLD)$(PROXY)$(_END)' program created. go!👻\n"

$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
				@$(CC) $(CFLAGS) -I$(DIR_HEADERS) -c $< -o $@
				@printf "$(_BACK) $(_YELLOW)Compiling $(_BOLD)$< $(_END)⌛"

clean:
	@printf "Removing $(_BOLD)object files$(_END) in '$(_YELLOW)$(_BOLD)$(DIR_OBJS)$(_END)'⌛"
	@$(RM) ${COMMON_OBJS} ${SERVER_OBJS} ${PROXY_OBJS}
	@printf "$(_BACK)All $(_BOLD)object files$(_END) removed in '$(_YELLOW)$(_BOLD)$(DIR_OBJS)$(_END)'✅\n"

fclean: clean
	@printf "Removing $(_BOLD)executable prgoram '$(_RED)$(NAME)/$(PROXY)$(_END)'⌛"
	@${RM} $(NAME) $(PROXY)
	@printf "$(_BACK)$(_BOLD)executable prgoram '$(_RED)$(_BOLD)$(NAME)/$(PROXY)$(_END)' removed⌛\n"

re: fclean all

.PHONY:	all clean fclean re bonus
