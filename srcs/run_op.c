/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:05:56 by estarck           #+#    #+#             */
/*   Updated: 2022/09/05 16:34:39 by reclaire         ###   ########.fr       */
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

void	run_op(t_data *shell, t_lst *cmd)
{
	if (cmd->heredoc || cmd->sep == D_LEFT)
	{
		init_heredoc(shell, cmd);
	}
	if (cmd->sep == S_LEFT)
		s_left(shell, cmd);
	else if (cmd->sep == S_RIGHT)
		s_right(shell, cmd);
	else if (cmd->sep == D_RIGHT)
		d_right(shell, cmd);
}
