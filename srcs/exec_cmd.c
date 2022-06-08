/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:11:42 by estarck           #+#    #+#             */
/*   Updated: 2022/06/08 12:10:28 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_builtin(t_shell *shell, t_cmd *cmd, int *pipefd, int j)
{
	pipefd_manag(shell, cmd, pipefd, j);
	if (cmd->blt == PWD)
		blt_pwd(shell);
	else
		printf("a coder\n");
}

static void	run_execve(t_shell *shell, t_cmd *cmd, int *pipefd, int j)
{
	pipefd_manag(shell, cmd, pipefd, j);
	execve (*cmd->cmd, cmd->cmd, shell->env);
}

static void	run_pipe(t_shell *shell)
{
	int		i;
	pid_t	pid;
	int		pipefd[2 * shell->nbr_pipe];
	t_cmd	*cmd;
	int	j = 0;

	cmd = shell->cmd;
	i = 0;
	for(i = 0; i < (shell->nbr_pipe); i++)
		pipe(pipefd + i * 2);
	while (cmd)
	{
		pid = fork();
		if (pid < 0)
			perror("error");
		if (pid == 0)
		{
			if (cmd->blt == 9)
				run_execve(shell, cmd, pipefd, j);
			else
				run_builtin(shell, cmd, pipefd, j);
		}
		cmd = cmd->next;
		j += 2;
	}
	for(i = 0; i < 2 * shell->nbr_pipe; i++)
		close(pipefd[i]);
	for(i = 0; i < shell->nbr_pipe + 1; i++)
		waitpid(-1, 0, 0);
}

void	exec_all(t_shell *shell)
{
	run_pipe(shell);
}
