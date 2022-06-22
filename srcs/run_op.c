/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:05:56 by estarck           #+#    #+#             */
/*   Updated: 2022/06/22 15:23:54 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_manager2(t_data *shell, t_lst *cmd, int fd)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	dup2(fd, STDOUT_FILENO);
	if (cmd->prev != NULL)
		dup2(cmd->prev->pipefd[READ], STDIN_FILENO);
	while (tmp)
	{
		close(tmp->pipefd[READ]);
		close(tmp->pipefd[WRITE]);
		tmp = tmp->next;
	}
}

/*void	fd_manager3(t_data *shell, t_lst *cmd, int fd)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	dup2(fd, STDIN_FILENO);
	if (cmd->next)
		dup2(cmd->pipefd[WRITE], STDOUT_FILENO);
	while (tmp)
	{
		close(tmp->pipefd[READ]);
		close(tmp->pipefd[WRITE]);
		tmp = tmp->next;
	}
}*/

static void	exec_op(t_data *shell, t_lst *cmd)
{
	if (cmd->sep == S_LEFT)
		s_left(shell, cmd);
	else if (cmd->sep == S_RIGHT)
		s_right(shell, cmd);
	else if (cmd->sep == D_RIGHT)
		d_right(shell, cmd);
	else if (cmd->sep == D_LEFT)
	{
		run_heredocs(shell, cmd);
		//exec_heredocs(shell, cmd);
	}
}

void	run_op(t_data *shell, t_lst *cmd)
{
	//if (cmd->built == 9)
		exec_op(shell, cmd);
	//else
	//	printf("a coder\n");
}
