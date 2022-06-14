/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:35:23 by estarck           #+#    #+#             */
/*   Updated: 2022/06/14 13:14:24 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <dirent.h>
# include "libft.h"

typedef enum e_bool
{
	FALSE,
	RIGHT
}	t_bool;

enum e_write
{
	READ,
	WRITE
};

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
	CMD = 9
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

typedef struct s_lst
{
	char			*p_cmd;
	char			**argv;
	int				built;
	int				sep;
	int				pipefd[2];
	int				error;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

typedef struct s_data
{
	char	*ret_prompt;
	t_lst	*cmd;
	char	*builtins[8];
	char	**env;
	char	**env_path;
}	t_data;

//Init
void	init_env_path(t_data *shell);
int		init_blt(t_data *shell, t_lst *cmd);

//Parsing
t_lst	*parse_prompt(t_data *shell);
int		find_cmd(t_data *shell);

//Parsing utils
t_lst	*add_cmd(t_lst *cmd);
t_lst	*new_cmd(void);
char	*ft_strcut(char *str, char tok);
int		count_argv(t_lst *cmd, char *str);

//Exec cmd
void	run_cmd(t_data *shell);

//Exec blt
void	exec_blt(t_data *shell, t_lst *cmd);
void	exec_cd(t_data *shell, t_lst *cmd);
void	exec_pwd(t_data *shell, t_lst *cmd);

//Free minishell
void	free_cmd(t_lst *cmd);

//syntax error
int		check_error(t_lst *cmd);
int		check_quote(t_lst *cmd, char *str);


#endif