/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:17 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/17 17:24:46 by reclaire         ###   ########.fr       */
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

int	special(t_data *shell, t_lst *cmd, char *arg)
{
	
}

void	parse_arg(t_data *shell, t_lst *cmd, char *arg, int spec)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			i += print_var(shell, cmd, arg + i + 1);
		else if (arg[i] == '\\' && spec)
			i += special(shell, cmd, arg + i + 1);
		else
			write(1, arg + i, 1);
		i++;
	}
}

void	exec_echo(t_data *shell, t_lst *cmd)
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
	while (cmd->argv[i])
	{
		parse_arg(shell, cmd, cmd->argv[i], special_chars);
		write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return ;
}
