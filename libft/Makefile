# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2022/05/18 15:11:26 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME	=	libft.a	
SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_getindex.c \
			ft_is_prime.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isdigit.c \
            ft_str_isnum.c \
			ft_isprint.c \
			ft_itoa.c \
            ft_min.c \
            ft_fmin.c \
            ft_max.c \
            ft_fmax.c \
            ft_isrange.c \
            ft_abs.c \
            ft_fabs.c \
            ft_str_appnd.c \
            ft_malloc.c \
			ft_magnitude.c \
			ft_pow.c \
			ft_range.c \
			ft_nrange.c \
			ft_uitoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strcat.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_wrap.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lstadd_front.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstremoveif.c \
			gnl/ft_gnl.c \
			gnl/ft_gnl2.c \
			ft_printf/ft_printf.c \
			ft_printf/handle_c.c \
			ft_printf/handle_d.c \
			ft_printf/handle_i.c \
			ft_printf/handle_p.c \
			ft_printf/handle_s.c \
			ft_printf/handle_u.c \
			ft_printf/handle_uX.c \
			ft_printf/handle_x.c

OBJS		=	${SRCS:.c=.o}
INCLUDES  	=	-I./ -I./gnl -I./ft_printf
CC			=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -O3
ifdef MOREFLAGS
CFLAGS		:=	$(CFLAGS) $(MOREFLAGS)
endif
RM			=	rm -f

_SRCSCOUNT	=	$(words $(SRCS))
_COUNT		=	0

%.o: %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS)
				
all:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_B)
			
fclean:		clean
			$(RM) $(NAME)

re:			fclean all clean

.PHONY:		fclean all clean re start