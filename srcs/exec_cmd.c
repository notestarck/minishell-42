/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:43:07 by estarck           #+#    #+#             */
/*   Updated: 2022/06/15 18:26:53y estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fd_manager(t_data *shell, t_lst *cmd)
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

static void	exec_cmd(t_data *shell, t_lst *cmd)
{
	if (execve(cmd->p_cmd, cmd->argv, shell->env) == -1)
		perror("error : execve");
		exit (0);
}

void run_cmd(t_data *shell)
{
	t_lst	*cmd;
	pid_t	pid;
	int		status;
	t_lst	*tmp;

	tmp = shell->cmd;
	cmd = shell->cmd;
	while (tmp)
	{
		pipe(tmp->pipefd);
		tmp = tmp->next;
	}
	tmp = shell->cmd;
	while (cmd)
	{
		pid = fork();
		if (pid < 0)
			perror ("fork");
		if (pid == 0)
		{
			fd_manager(shell, cmd);
			if (cmd->built == 9)
				exec_cmd(shell, cmd);
			else
			{
				exec_blt(shell, cmd);
				exit(0) ;
			}
		}
		cmd = cmd->next;
	}
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
		tmp = tmp->next;
	}
}
