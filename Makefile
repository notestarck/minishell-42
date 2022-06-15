NAME	=	minishell

INCLUDE	=	-I./includes \
			-I./libft/includes

LIBFT	=	-L./libft -lft			
LIB		=	-lreadline

SRCS_D	=	./srcs
SRCS	=	main.c \
			init_path.c \
			parsing.c \
			parsing_utils.c \
			syntax_error.c \
			init_blt.c \
			exec_cmd.c \
			free_shell.c \
			find_cmd.c \
			exec_blt.c \
			cd.c \
			pwd.c \
			export.c
_SRCS	=	$(patsubst %,$(SRCS_D)/%,$(SRCS))

OBJS_D	=	./objs
OBJS	=	${SRCS:.c=.o}
_OBJS	=	$(patsubst %,$(OBJS_D)/%,$(OBJS))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

# Mise en forme
_END	=	$'\x1b[0m
_BOLD	=	$'\x1b[1m
_UNDER	=	$'\x1b[4m
_REV	=	$'\x1b[7m

# Couleurs
_GREY	=	$'\x1b[30m
_RED	=	$'\x1b[31m
_GREEN	=	$'\x1b[32m
GREEN	=	\033[1;32m
_YELLOW	=	$'\x1b[33m
_BLUE	=	$'\x1b[34m
_PURPLE	=	$'\x1b[35m
_CYAN	=	$'\x1b[36m
_WHITE	=	$'\x1b[37m

all		:	$(NAME)

$(NAME)	:	$(_OBJS)
			@echo "$(_RED)Compilation libft.a en cours...$(_END)"
			@make -C ./libft
			@echo "$(_RED)Compilation minishell en cours...$(_END)"
			@$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT) $(LIB) $(_OBJS) -o $(NAME)
			@echo "$(_GREEN)$(_BOLD)Fin de la compilation de minishell$(_END)"

$(OBJS_D)/%.o: $(SRCS_D)/%.c
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean	:	
			@echo "$(_BLUE)Clean des .o$(_END)"
			@make -C ./libft clean
			@$(RM) $(_OBJS)
			@$(RM) -rf objs

fclean	:	clean
			@echo "$(_BLUE)Clean des executables$(_END)"
			@$(RM) ./libft/libft.a
			@$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re