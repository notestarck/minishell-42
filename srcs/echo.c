/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:17 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/23 11:01:27 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special(char *arg)
{
	if (*arg == 'a')
		write(1, "\a", 1);
	if (*arg == 'b')
		write(1, "\b", 1);
	if (*arg == 't')
		write(1, "\t", 1);
	if (*arg == 'n')
		write(1, "\n", 1);
	if (*arg == 'v')
		write(1, "\v", 1);
	if (*arg == 'f')
		write(1, "\f", 1);
	if (*arg == 'r')
		write(1, "\r", 1);
	return (1);
}

void	echo_parse(char *arg, int spec)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\' && spec)
			i += special(arg + i + 1);
		else
			write(1, arg + i, 1);
		i++;
	}
}

void	exec_echo(t_lst *cmd)
{
	int	i;
	int	j;
	int	newline;
	int	special_chars;

	newline = 1;
	special_chars = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] != '-')
			break ;
		j = 1;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == 'n')
				newline = 0;
			else if (cmd->argv[i][j] == 'e')
				special_chars = 1;
			else if (cmd->argv[i][j] == 'E')
				special_chars = 0;
			else
				break ;
			j++;
		}
		if (cmd->argv[i][j] != '\0')
			break ;
		i++;
	}
	echo_parse(cmd->argv[i], special_chars);
	i++;
	while (cmd->argv[i])
	{
		write(1, " ", 1);
		echo_parse(cmd->argv[i], special_chars);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return ;
}
