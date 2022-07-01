/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:17 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/30 20:31:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_print(t_arg **args, int newline)
{
	int	i;
	int	j;	

	i = 0;
	while (args[i])
	{
		if (args[i]->type != ARG)
			break ;
		j = 0;
		while (args[i]->str[j])
		{
			write(1, args[i]->str + j, 1);
			j++;
		}
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

void	exec_echo(t_lst *cmd)
{
	int	i;
	int	j;
	int	newline;

	newline = 1;
	i = 1;
	while (cmd->argv[i])
	{
		if (cmd->argv[i]->str[0] != '-')
			break ;
		j = 1;
		while (cmd->argv[i]->str[j])
		{
			if (cmd->argv[i]->str[j] == 'n')
				newline = 0;
			else
				break ;
			j++;
		}
		if (cmd->argv[i]->str[j] != '\0')
			break ;
		i++;
	}
	echo_print(cmd->argv + i, newline);
}
