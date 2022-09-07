/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:17 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/07 16:40:34 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_tild(t_data *shell)
{
	ft_printf("%s", env_get(shell, "HOME"));
}

static void	echo_print(t_data *shell, t_arg **args, int newline)
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
			if (ft_strcmp(args[i]->str, "~") == 0 && args[i]->d_quotes == NULL
				&& args[i]->s_quotes == NULL)
				echo_tild(shell);
			else
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

void	exec_echo(t_data *shell, t_lst *cmd)
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
	echo_print(shell, cmd->argv + i, newline);
}
