/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:52:10 by estarck           #+#    #+#             */
/*   Updated: 2022/06/08 13:05:47 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipefd_manag(t_shell *shell, t_cmd *cmd, int *pipefd, int j)
{
	int	i;

	i = 0;
	if (cmd->next)
		dup2 (pipefd[j + 1], STDOUT_FILENO);
	if (j != 0)
		dup2(pipefd[j - 2], STDIN_FILENO);
	while (i < 2 * shell->nbr_pipe)
		close (pipefd[i++]);
}

void	blt_pwd(t_shell *shell)
{
	int	i;

	i = 0;
	while (ft_strncmp(shell->env[i], "PWD=", 4))
		i++;
	ft_putstr_fd(shell->env[i] + 4, 1);
	ft_putchar_fd('\n', 1);
}