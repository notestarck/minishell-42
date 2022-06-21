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

static void	close_fd(t_data *shell, t_lst *cmd)
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

	tmp = shell->cmd;
	while (tmp)
	{
		pipe(tmp->pipefd);
		tmp = tmp->next;
	}
	tmp = shell->cmd;
	while (tmp)
	{
		exec_cmd(shell, tmp);
		tmp = tmp->next;
	}
	close_fd(shell, tmp);
}
