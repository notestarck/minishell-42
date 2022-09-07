# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2022/09/07 16:22:47 by estarck          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.DEFAULT_GOAL := all
NAME		=	minishell
SRCS		=	$(shell find srcs/ -type f -name '*.c')
OBJS		=	${SRCS:.c=.o}

INCLUDES  	=	-I./includes -I./libft -I/Users/$(USER)/.brew/opt/readline/include
CC			=	gcc
#CFLAGS		:=	-Wall -Wextra -Werror -O3 
CFLAGS		:=	-Wall -Wextra -Werror -g
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
			$(CC) $(CFLAGS) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib $(OBJS) libft.a -o $(NAME)


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
