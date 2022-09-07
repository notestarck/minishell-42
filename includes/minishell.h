/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:35:23 by estarck           #+#    #+#             */
/*   Updated: 2022/09/07 18:58:21 by reclaire         ###   ########.fr       */
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

# define ANY_ERROR 1
# define COMMAND_NOT_FOUND 127
# define EXIT_ERROR_ARG 255
# define INPUT_ERROR 256
# define SYNTAX_ERROR 258

extern pid_t	g_pid;

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

typedef struct e_pars_dat
{
	t_list	*args;
	t_list	*lst_s_quotes;
	t_list	*lst_d_quotes;
	char	*str;
	char	*new;
	int		i;
	int		escape;
	int		s_quote;
	int		d_quote;
	int		d_quote_escape;
	int		err;
}	t_pars_dat;

typedef enum e_type
{
	ARG = -1,
	S_RIGHT,
	S_LEFT,
	D_RIGHT,
	D_LEFT,
	PIPE,
	AND,
	OR,
	WLCRD
}	t_type;

typedef struct s_arg
{
	t_type	type;
	char	*str;
	t_list	*s_quotes;
	t_list	*d_quotes;
}	t_arg;

typedef struct s_lst
{
	char			*p_cmd;
	t_arg			**argv;
	char			*tmpfile;
	int				built;
	int				sep;
	int				heredoc;
	int				pipefd[2];
	int				error;
	int				er_quote;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

typedef struct s_data
{
	char	*ret_prompt;
	t_lst	*cmd;
	t_list	*cmd_list;
	int		nbr_cmd;
	char	*builtins[8];
	char	**env;
	char	**env_path;
	int		code_error;
	int		seed;
	int		test;
}	t_data;

//Init
void		init_env_path(t_data *shell);
int			init_blt(t_data *shell, t_lst *cmd);

//Parsing
void		parse_prompt(t_data *shell);
int			find_cmd(t_data *shell);
int			valid_path(t_data *shell, char *av);
void		append_char(t_pars_dat *d, char **str, char c, int t);
void		init_cmd(t_data *shell);
void		cpy_cmd(t_data *shell);
void		check_redir(t_lst *cmd, int i);
void		push(t_pars_dat *d, t_type type);
t_pars_dat	*create_dat(t_data *shell);
void		add_quote(t_pars_dat *d, int t, int v, int j);
int			handle_redir(t_pars_dat *d, char c, int size, t_type type);
int			handle_s_quotes(t_pars_dat *d);
int			handle_d_quotes(t_pars_dat *d);

//Parsing utils
t_lst		*add_cmd(t_lst *cmd);
t_lst		*new_cmd(void);
int			cmp(t_arg *data, void *ref);
int			is_in_quotes(int i, t_arg *arg);

//Exec cmd
void		run_cmd(t_data *shell);
void		fd_manager(t_data *shell, t_lst *cmd);
char		**t_arg_to_char(t_arg **cmd);
void		exec_cmd(t_data *shell, t_lst *cmd);
void		insert_var_inter(t_data *shell, char **arg, int start);

//Exec op
void		run_op(t_data *shell, t_lst *cmd);
void		fd_manager2(t_data *shell, t_lst *cmd, int fd);
void		init_heredoc(t_data *shell, t_lst *cmd);
void		repars_heredocs(t_lst *cmd);
void		s_left(t_data *shell, t_lst *cmd);
void		s_right(t_data *shell, t_lst *cmd);
void		d_right(t_data *shell, t_lst *cmd);
int			pre_process(t_data *shell);

//Exec cmd utils
void		parse_args(t_data *shell, t_lst *cmd);
int			ft_rand(t_data *shell);
int			insert_var(t_data *shell, t_arg *arg, int start);

//Exec blt
void		builtin(t_data *shell, t_lst *cmd);
void		exec_blt(t_data *shell, t_lst *cmd);
void		exec_cd(t_data *shell, t_lst *cmd);
void		exec_pwd(t_data *shell);
void		exec_env(t_data *shell);
void		exec_export(t_data *shell, t_lst *cmd);
void		exec_unset(t_data *shell, t_lst *cmd);
void		exec_echo(t_data *shell, t_lst *cmd);
void		exec_exit(t_data *shell, t_lst *tmp);

//Free minishell
void		free_cmd(t_lst *cmd);
void		free_all(t_data *shell);
void		free_arg(void *t);

//syntax error
int			check_error(t_data *shell, t_lst *cmd);
int			check_quote(t_lst *cmd, char *str);
void		check_syntax(t_data *shell);

//Utils
void		init_env(t_data *shell, char **env);
char		*env_get(t_data *shell, char *key);
void		env_set(t_data *shell, char *key, char *value);
void		env_new(t_data *shell, char *key, char *value);
void		env_del(t_data *shell, char *key);

//Quit
void		quit_mini(t_data *shell);

#endif