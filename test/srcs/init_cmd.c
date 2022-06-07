/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:05:01 by estarck           #+#    #+#             */
/*   Updated: 2022/06/07 14:25:53 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_cmd(t_cmd *cmd)
{
	cmd->cmd = malloc(sizeof(char *) * 4);
	cmd->cmd[0] = "/bin/bash";
	cmd->cmd[1] = "-c";
	//cmd->cmd[2] = "-i";
	//cmd->cmd[2] = "-s";
	cmd->cmd[2] = cmd->argv;
	cmd->cmd[3] = NULL;
}

static int	find_cmd(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (cmd->argv[i] == ' ' && cmd->argv[i] != '\0')
		i++;
	while (shell->builtins[y] != NULL)
	{
		if (!ft_strncmp(&cmd->argv[i], shell->builtins[y], ft_strlen(shell->builtins[i]) + 1))
		{
			return (0);
		}
		y++;
	}
	return (1);
}

void	init_cmd(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		if (find_cmd(shell, tmp))
	{
			write_cmd(tmp);
	}
		else
			printf("a coder\n");
		tmp = tmp->next;
	}
}