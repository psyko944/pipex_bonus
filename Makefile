#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkherbou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 06:26:53 by mkherbou          #+#    #+#              #
#    Updated: 2023/12/19 19:35:14 by mekherbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex 

SRCS = srcs/main.c \
srcs/get_cmd.c \
srcs/init.c \
srcs/utils.c 

S1="================================================================================"

OBJS := ${SRCS:.c=.o}

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
PURPLE= \033[38;2;255;105;180m
RESET= \033[0m

CC = clang

RM = rm -f

INC_DIR = Inc
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -g3

.c.o:
	@${CC} ${CFLAGS} -c -I ${INC_DIR} $< -o ${<:.c=.o}
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"

all:
	@echo "$(PURPLE)$(S1)\n"
	@echo "$(PURPLE)██████╗ ██╗██████╗ ███████╗██╗  ██╗"
	@echo "$(PURPLE)██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "$(PURPLE)██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "$(PURPLE)██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "$(PURPLE)██║     ██║██║     ███████╗██╔╝ ██╗"
	@echo "$(PURPLE)╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"
	@echo "\n$(PURPLE)$(S1)"

	@$(MAKE) -j $(NAME)
	@echo "$(GREEN)pipex compiled!$(DEF_COLOR)"

${LIBFT}:
	$(MAKE) -C $(LIBFT_DIR)
$(NAME): ${OBJS} ${LIBFT}
		${CC} $(CFLAGS) ${OBJS} ${LIBFT} -o $(NAME)
clean:
	@${RM} ${OBJS}
	@echo "$(BLUE)pipex object files cleaned!$(DEF_COLOR)"

fclean: clean
	@${RM} $(NAME) 
	@echo "$(CYAN) ${NAME} have been deleted$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for pipex!$(DEF_COLOR)"

.PHONY: all clean fclean re 
