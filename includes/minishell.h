/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:35:23 by estarck           #+#    #+#             */
/*   Updated: 2022/06/24 17:28:53 by reclaire         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
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
	S_RIGHT,
	S_LEFT,
	D_RIGHT,
	D_LEFT,
	AND,
	OR ,
	WLCRD
};

typedef struct s_lst
{
	char			*p_cmd;
	char			**argv;
	char			*tmpfile;
	int				built;
	int				sep;
	int				heredoc;
	int				pipefd[2];
	int				error;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

typedef struct s_data
{
	char	*ret_prompt;
	t_lst	*cmd;
	int		nbr_cmd;
	char	*builtins[8];
	char	**env;
	char	**env_path;
	int		code_error;
	int		seed;
	int		test;
}	t_data;

static pid_t	g_pid;

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
int		count_argv(t_data *shell, t_lst *cmd, char *str);

//Exec cmd
void	run_cmd(t_data *shell);
void	fd_manager(t_data *shell, t_lst *cmd);

//Exec op
void	run_op(t_data *shell, t_lst *cmd);
void	fd_manager2(t_data *shell, t_lst *cmd, int fd);
void	init_heredoc(t_lst *cmd);
//void	fd_manager3(t_data *shell, t_lst *cmd, int fd);
void	s_left(t_data *shell, t_lst *cmd);
void	s_right(t_data *shell, t_lst *cmd);
void	d_right(t_data *shell, t_lst *cmd);

//Exec cmd utils
void	parse_args(t_data *shell, t_lst *cmd);
int		ft_rand(t_data *shell);
void	remove_quotes(t_lst *cmd);
int		insert_var(t_data *shell, char **arg, int start);

//Exec blt
void	builtin(t_data *shell, t_lst *cmd);
void	exec_blt(t_data *shell, t_lst *cmd);
void	exec_cd(t_data *shell, t_lst *cmd);
void	exec_pwd(t_data *shell, t_lst *cmd);
void	exec_env(t_data *shell);
void	exec_export(t_data *shell, t_lst *cmd);
void	exec_unset(t_data *shell, t_lst *cmd);
void	exec_echo(t_lst *cmd);

//Free minishell
void	free_cmd(t_lst *cmd);

//syntax error
int		check_error(t_lst *cmd);
int		check_quote(t_lst *cmd, char *str);
void	check_syntax(t_data *shell);

//Utils
char	*env_get(t_data *shell, char *key);
void	env_set(t_data *shell, char *key, char *value);
void	env_new(t_data *shell, char *key, char *value);
void	env_del(t_data *shell, char *key);

//Quit
void	quit_mini(int sig, t_data *shell);

#endif