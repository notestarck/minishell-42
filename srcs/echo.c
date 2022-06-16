/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:17 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/16 23:27:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_var(t_data *shell, t_lst *cmd, char *arg)
{
	int		i;
	char	*val;
	char	*key;

	i = 0;
	while (ft_isalnum(arg[i]))
		i++;
	key = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(key, arg, i + 1);
	val = env_get(shell, key);
	i = ft_strlen(val);
	write(1, val, i);
	free(val);
	return (i);
}

void	parse_arg(t_data *shell, t_lst *cmd, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			i += print_var(shell, cmd, arg + i + 1);
		else
			write(1, arg + i, 1);
		i++;
	}
}

void	exec_echo(t_data *shell, t_lst *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->argv[i])
	{
		parse_arg(shell, cmd, cmd->argv[i]);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return ;
}
