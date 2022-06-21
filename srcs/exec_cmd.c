/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:50:27 by estarck           #+#    #+#             */
/*   Updated: 2022/06/21 12:00:10 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_data *shell, t_lst *cmd, int *stin, int *stout)
{
	if (cmd->prev != 0)
		close (cmd->prev->pipefd[READ]);
	close (cmd->pipefd[WRITE]);
	if (cmd->next == 0)
		close (cmd->pipefd[READ]);
	dup2(*stin, STDIN_FILENO);
	dup2(*stout, STDOUT_FILENO);
	close(*stin);
	close(*stout);
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
	int		status;
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
	else
	{
		close (cmd->pipefd[WRITE]);
		waitpid(pid, &status, 0);
	}
}

static void	exec_cmd(t_data *shell, t_lst *cmd)
{
	if (cmd->built != 9)
	{
		builtin(shell, cmd);
		return ;
	}
	//else if (cmd->built == 9 && cmd->sep != -1)
	//{
	//	//a coder
	//}
	else
		exec_path(shell, cmd);
}

void	run_cmd(t_data *shell)
{
	t_lst	*tmp;
	int		stin;
	int		stout;

	tmp = shell->cmd;
	while (tmp)
	{
		pipe(tmp->pipefd);
		stin = dup(0);
		stout = dup(1);
		exec_cmd(shell, tmp);
		close_fd(shell, tmp, &stin, &stout);
		tmp = tmp->next;
	}
}
