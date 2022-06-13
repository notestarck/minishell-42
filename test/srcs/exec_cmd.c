/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:43:07 by estarck           #+#    #+#             */
/*   Updated: 2022/06/13 15:38:59 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *shell)
{
	pid_t	pid;
	int		status;
	t_lst	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		pipe(cmd->pipefd);
		pid = fork();
		if (pid == -1)
			perror ("fork");
		else if (pid == 0)
		{
			if (cmd->next)
				dup2(cmd->pipefd[WRITE], STDOUT_FILENO);
			if (cmd->prev != NULL)
				dup2(cmd->prev->pipefd[READ], STDIN_FILENO);
			close (cmd->pipefd[READ]);
			if (execve(cmd->p_cmd, cmd->argv, shell->env) == -1)
				perror("error : execve");
		}
		else
		{
			close(cmd->pipefd[WRITE]);
			waitpid(pid, &status, 0);
			cmd = cmd->next;
		}
	}
}
