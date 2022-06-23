/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:50:27 by estarck           #+#    #+#             */
/*   Updated: 2022/06/21 11:57:36by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_data *shell)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		close(tmp->pipefd[READ]);
		close(tmp->pipefd[WRITE]);
		tmp = tmp->next;
	}
	tmp = shell->cmd;
	while (tmp)
	{
		waitpid(-1, 0, 0);
		if (tmp->built == EXIT)
			quit_mini(2);
		tmp = tmp->next;
	}
}

void	fd_manager(t_data *shell, t_lst *cmd)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	if (cmd->next)
		dup2(cmd->pipefd[WRITE], STDOUT_FILENO);
	if (cmd->prev != NULL)
		dup2(cmd->prev->pipefd[READ], STDIN_FILENO);
	while (tmp)
	{
		close(tmp->pipefd[READ]);
		close(tmp->pipefd[WRITE]);
		tmp = tmp->next;
	}
}

static void	exec_path(t_data *shell, t_lst *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror ("fork");
	if (pid == 0)
	{
		fd_manager(shell, cmd);
		if (execve(cmd->p_cmd, cmd->argv, shell->env) == -1)
			perror("error : execve");
	}
}

int	insert_var(t_data *shell, char **arg, int start)
{
	char	*key;
	char	*out;
	char	*value;
	int		i;

	i = 1;
	while ((*arg)[start + i] && ft_isalnum((*arg)[start + i]))
		i++;
	key = malloc(sizeof(char) * i);
	ft_strlcpy(key, (*arg) + start + 1, i);
	value = env_get(shell, key);
	out = ft_substr(*arg, 0, start);
	out = ft_str_appnd(out, value, 1, 1);
	out = ft_str_appnd(out, *arg + start + i, 1, 0);
	free(*arg);
	*arg = out;
	return (start + i - 1);
}

void	remove_quotes(t_lst *cmd)
{
	int		i;
	int		j;
	int		count;
	char	*str;

	i = 0;
	while (cmd->argv[i])
	{
		j = 0;
		count = 0;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == '\'' || cmd->argv[i][j] == '\"')
				count++;
			j++;
		}
		str = ft_malloc(sizeof(char) * (ft_strlen(cmd->argv[i]) - count + 1));
		j = 0;
		count = 0;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] != '\'' && cmd->argv[i][j] != '\"')
			{
				str[count] = cmd->argv[i][j];
				count++;
			}
			j++;
		}
		str[count] = '\0';
		free(cmd->argv[i]);
		cmd->argv[i] = str;
		i++;
	}
}

void	parse_args(t_data *shell, t_lst *cmd)
{
	int		i;
	int     j;
	int     is_simple_quote;
	int     is_double_quote;

	i = 0;
	is_simple_quote = 0;
	is_double_quote = 0;
	while (cmd->argv[i])
	{
		j = 0;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == '\'')
			{
				if (is_simple_quote)
					is_simple_quote = 0;
				else
					is_simple_quote = 1;
			}
			if (cmd->argv[i][j] == '\"')
			{
				if (is_double_quote)
					is_double_quote = 0;
				else
					is_double_quote = 1;
			}
			if (cmd->argv[i][j] == '$' && !is_simple_quote)
				j = insert_var(shell, &(cmd->argv[i]), j);
			j++;
		}
		i++;
	}
}

static void	exec_cmd(t_data *shell, t_lst *cmd)
{
	parse_args(shell, cmd);
	remove_quotes(cmd);
	if (cmd->built != 9 && cmd->sep == -1)
		builtin(shell, cmd);
	else if (cmd->sep != -1)
		run_op(shell, cmd);
	else
		exec_path(shell, cmd);
}

void	run_cmd(t_data *shell)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		pipe(tmp->pipefd);
		tmp = tmp->next;
	}
	tmp = shell->cmd;
	while (tmp)
	{
		if (tmp->heredoc)
			init_heredoc(tmp);
		exec_cmd(shell, tmp);
		tmp = tmp->next;
	}
	close_fd(shell);
}
