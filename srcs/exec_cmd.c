/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:43:07 by estarck           #+#    #+#             */
/*   Updated: 2022/06/15 00:06:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_data *shell, t_lst *cmd)
{
	if (cmd->next)
		dup2(cmd->pipefd[WRITE], STDOUT_FILENO);
	if (cmd->prev != NULL)
		dup2(cmd->prev->pipefd[READ], STDIN_FILENO);
	close (cmd->pipefd[READ]);
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
			cmd = cmd->next;
		}
	}
}
