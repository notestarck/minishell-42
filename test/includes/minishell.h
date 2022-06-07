/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:43:38 by estarck           #+#    #+#             */
/*   Updated: 2022/06/07 15:54:42 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include "libft.h"

enum e_built
{
	UNKNOW = -1,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	ERROR = 9
};

enum e_sep
{
	NONE = -1,
	PIPE,
	COMA,
	S_RIGHT,
	S_LEFT,
	D_RIGHT,
	D_LEFT,
	AND,
	OR
};

enum e_write
{
	READ,
	WRITE
};

typedef enum e_bool
{
	FALSE,
	RIGHT
}	t_bool;

typedef struct s_cmd
{
	char			**cmd;
	char			*argv;
	//char			*input;
	//char			*output;
	//struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	char	*pwd;
	int		nbr_pipe;
	char	*builtins[8];
	char	*ret_prompt;
	int		error;
	t_cmd	*cmd;
}	t_shell;

//Gestion des erreurs
void	ft_perror(char	*err_mess, t_shell *shell, int free_lvl);

//Parsing
int		parsing(t_shell *shell);

//Parsing utils
t_cmd	*add_lst(t_shell *shell);
int		count_argv(t_shell *shell, char *str);
int		argv_length(t_shell *shell, char *str);

//Gestion syntax
int		check_error(t_shell *shell);
int		check_quote(t_shell *shell, char *str);

//path cmd
void	init_cmd(t_shell *shell);

//Exec cmd
void		exec_all(t_shell *shell);

//Gestion free
void	ft_free(t_shell *shell);



#endif