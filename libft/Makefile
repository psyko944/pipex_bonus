# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mekherbo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 15:06:56 by mekherbo          #+#    #+#              #
#    Updated: 2023/11/11 15:07:08 by mekherbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_atoi.c		\
	ft_isascii.c	\
	ft_isalnum.c	\
	ft_isalpha.c	\
	ft_isdigit.c	\
	ft_isprint.c	\
	ft_split.c		\
	ft_strjoin.c	\
	ft_strdup.c	\
	ft_strlcpy.c	\
	ft_strlcat.c	\
	ft_strlen.c	\
	ft_strnstr.c	\
	ft_tolower.c	\
	ft_toupper.c	\
	ft_itoa.c		\
	ft_memcmp.c	\
	ft_memcpy.c	\
	ft_putstr_fd.c	\
	ft_putchar_fd.c	\
	ft_putnbr_fd.c	\
	ft_calloc.c	\
	ft_putendl_fd.c	\
	ft_strncmp.c	\
	ft_bzero.c		\
	ft_strchr.c	\
	ft_strrchr.c	\
	ft_memmove.c	\
	ft_memset.c	\
	ft_memchr.c	\
	ft_substr.c	\
	ft_strmapi.c	\
	ft_striteri.c	\
	ft_strtrim.c

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
             ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
             ft_lstiter.c ft_lstmap.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = libft.a

HEADER = includes

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

${NAME}: 	${OBJS}
				ar -rcs ${NAME} ${OBJS}

%.o: %.c
		${CC} -c ${FLAGS} -o $@ $< -I ${HEADER}

all :  ${NAME}

bonus: $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
		
clean:
		${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
			${RM} ${NAME}
			@echo " ${NAME} have been deleted"

re:	fclean all

.PHONY: all clean fclean re bonus
