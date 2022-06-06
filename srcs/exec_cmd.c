/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:11:42 by estarck           #+#    #+#             */
/*   Updated: 2022/06/06 12:20:58 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_shell *shell)
{
	pid_t	pid;
	int		pipefd[2];
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd != NULL)
	{
		if (pipe(pipefd) == -1)
		{
			perror("error : pipe");
			return (0);
		}
		pid = fork();
		if (pid == -1)
		{
			perror ("error : fork");
			return (0);
		}
		if (pid == 0)
		{
			close (pipefd[READ]);
			if (cmd->next != NULL)
			{
				dup2(pipefd[WRITE], STDOUT_FILENO);
			}
			execve(cmd->cmd, cmd->argv, NULL);
			perror("error : execve");
		}
		else
		{
			close (pipefd[WRITE]);
			dup2(pipefd[READ], STDIN_FILENO);
			wait (NULL);
			cmd = cmd->next;
		}
	}
	return (0);
}

void	exec_all(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror ("error : fork");
	}
	if (pid == 0)
	{
		exec_cmd(shell);
	}
	else
	{
		wait (NULL);
	}
}