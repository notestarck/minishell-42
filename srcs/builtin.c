/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:31:57 by estarck           #+#    #+#             */
/*   Updated: 2022/06/23 20:03:28 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_blt(t_data *shell, t_lst *cmd)
{
	if (cmd->built == CD)
		exec_cd(shell, cmd);
	else if (cmd->built == PWD)
		exec_pwd(shell, cmd);
	else if (cmd->built == ENV)
		exec_env(shell);
	else if (cmd->built == EXPORT)
		exec_export(shell, cmd);
	else if (cmd->built == UNSET)
		exec_unset(shell, cmd);
	else if (cmd->built == ECHO)
		exec_echo(cmd);
	else if (cmd->built == EXIT)
		return ;
	return ;
}

static void	set_fork_builtin(t_data *shell, t_lst *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror ("fork");
	if (pid == 0)
	{
		fd_manager(shell, cmd);
		exec_blt(shell, cmd);
		exit(0);
	}
	else
	{
		close(cmd->pipefd[WRITE]);
		waitpid(pid, &status, 0);
	}
}

void	builtin(t_data *shell, t_lst *cmd)
{
	if (cmd->built == PWD || cmd->built == ECHO || cmd->built == ENV)
	{
		set_fork_builtin(shell, cmd);
		return ;
	}
	else if (cmd->built == CD || cmd->built == EXIT || cmd->built == EXPORT || cmd->built == UNSET)
	{
		exec_blt(shell, cmd);
		return ;
	}
}
