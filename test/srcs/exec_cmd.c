/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:43:07 by estarck           #+#    #+#             */
/*   Updated: 2022/06/09 11:39:08 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *shell)
{
	pid_t	pid;
	int		status;
	t_lst	*cmd;

	cmd = shell->cmd;
	pid = fork();
	if (pid == -1)
		perror ("fork");
	else if (pid == 0)
	{
		if (execve(cmd->p_cmd, cmd->argv, shell->env) == -1)
			perror("error : execve");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
