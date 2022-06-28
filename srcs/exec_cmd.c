/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:25:02 by estarck           #+#    #+#             */
/*   Updated: 2022/06/28 17:36:19 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

static void	close_fd(t_data *shell)
{
	t_lst	*tmp;
	int		signal;

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
		waitpid(-1, &signal, WUNTRACED);
		shell->code_error = signal % 255;
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
	if (cmd->heredoc)
		dup2(cmd->pipefd[READ], STDIN_FILENO);
	while (tmp)
	{
		close(tmp->pipefd[READ]);
		close(tmp->pipefd[WRITE]);
		tmp = tmp->next;
	}
}

static void	exec_path(t_data *shell, t_lst *cmd)
{
	g_pid = fork();
	if (g_pid < 0)
		perror ("fork");
	if (g_pid == 0)
	{
		fd_manager(shell, cmd);
		if (execve(cmd->p_cmd, cmd->argv, shell->env) == -1)
		{
			perror("error : execve");
			exit (126);
		}
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
		{
			tmp->tmpfile = ft_strdup("/tmp/minishell-tmp-");
			tmp->tmpfile = ft_str_appnd(tmp->tmpfile,
					ft_itoa(ft_rand(shell)), 1, 1);
			init_heredoc(tmp);
		}
		exec_cmd(shell, tmp);
		tmp = tmp->next;
	}
	close_fd(shell);
}
