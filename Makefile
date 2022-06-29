# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2022/06/29 15:49:00 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
NAME		=	minishell
SRCS		=	${wildcard srcs/*.c}
OBJS		=	${SRCS:.c=.o}

INCLUDES  	=	-I./includes -I./libft -I/Users/reclaire/.brew/opt/readline/include
CC			=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -O3 
#CFLAGS		:=	-g
ifdef MOREFLAGS
CFLAGS		:=	$(CFLAGS) $(MOREFLAGS)
endif
RM			=	rm -f

%.o: %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft.a:
			$(MAKE) -C ./libft
			cp libft/libft.a .

$(NAME):	libft.a $(OBJS)
			$(CC) $(CFLAGS) -lreadline -L/Users/reclaire/.brew/opt/readline/lib $(OBJS) libft.a -o $(NAME)

all:		$(NAME)

clean:
			$(MAKE) clean -C ./libft
			$(RM) $(OBJS) $(OBJS_B)
			
fclean:		clean
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME)
			$(RM) libft.a

re:			fclean all clean

.PHONY:		fclean all clean re
