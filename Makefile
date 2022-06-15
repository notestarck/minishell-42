# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2022/06/15 16:32:22 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
NAME		=	minishell
SRCS		=	${wildcard srcs/*.c}
OBJS		=	${SRCS:.c=.o}

INCLUDES  	=	-I./includes -I./libft/includes
CC			=	gcc
#CFLAGS		:=	-Wall -Wextra -Werror -O3
CFLAGS		:=	-O3 -lreadline
RM			=	rm -f
ifdef MOREFLAGS
CFLAGS		:=	$(CFLAGS) $(MOREFLAGS)
endif

%.o: %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft.a:
			$(MAKE) -C ./libft
			cp libft/libft.a .

$(NAME):	libft.a $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) libft.a -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_B)
			
fclean:		clean
			$(RM) $(NAME)

re:			fclean all clean

.PHONY:		fclean all clean re
