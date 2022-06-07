# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 21:25:34 by estarck           #+#    #+#              #
#    Updated: 2022/04/14 09:33:20 by estarck          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRCS	= 	ft_atoi.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memcmp.c \
			ft_strncmp.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_bzero.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_striteri.c \
			ft_calloc.c \
			ft_memchr.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_itoa.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strmapi.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_split.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_printf.c \
			srcs/ft_printf_utils.c \
			srcs/ft_printhexa.c \
			srcs/ft_ptrhexa.c \
			srcs/ft_uitoa.c \
			get_next_line.c \
			srcs/get_next_line_utils.c \
			ft_htol.c
OBJS	= ${SRCS:.c=.o}
HEADER	= ./includes
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
RM		= rm -f

.c.o:
			@${CC} ${CFLAGS} -I${HEADER} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}	
			@ar rc $(NAME) ${OBJS}

all:		${NAME}

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}	

re:			fclean all

.PHONY: 	all libft.a clean fclean re 