/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:43:07 by estarck           #+#    #+#             */
/*   Updated: 2022/06/15 11:44:38 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_data *shell, t_lst *cmd)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	if (cmd->prev != NULL)
		dup2(cmd->prev->pipefd[READ], STDIN_FILENO);
	if (cmd->next)
		dup2(cmd->pipefd[WRITE], STDOUT_FILENO);
	while (tmp)
	{
		close(cmd->pipefd[READ]);
		close(cmd->pipefd[WRITE]);
		tmp = tmp->next;
	}
	if (execve(cmd->p_cmd, cmd->argv, shell->env) == -1)
		perror("error : execve");
}

void run_cmd(t_data *shell)
{
	t_lst	*cmd;
	pid_t	pid;
	int		status;

	cmd = shell->cmd;
	while (cmd)
	{
		pipe(cmd->pipefd);
		pid = fork();
		if (pid == -1)
			perror ("fork");
		else if (pid == 0)
		{
			if (cmd->built == 9)
				exec_cmd(shell, cmd);
			else
			{
				exec_blt(shell, cmd);
				return ;
			}
		}
		else
		{
			close(cmd->pipefd[WRITE]);
			waitpid(pid, &status, 0);
			if (cmd->prev != NULL)
				close(cmd->prev->pipefd[READ]);
			if (cmd->next == NULL)
				close(cmd->pipefd[READ]);
			cmd = cmd->next;
		}
	}
}
