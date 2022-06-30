/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:10:03 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 17:34:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_rand(t_data *shell)
{
	shell->seed = (shell->seed * 1103515245U + 12345U) & 0x7fffffffU;
	return ((int)shell->seed);
}

void	parse_args(t_data *shell, t_lst *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->argv[i])
	{
		j = 0;
		while (cmd->argv[i]->str[j])
		{
			if (cmd->argv[i]->str[j] == '$' && cmd->argv[i]->str[j + 1] != '\0'
				&& is_in_quotes(j, cmd->argv[i]) != 1)
				ft_printf("REPLACE VAR\n");
				//j += insert_var(shell, &(cmd->argv[i]), j);
			j++;
		}
		i++;
	}
}

void	remove_quotes(t_lst *cmd)
{
	int		i;
	int		j;
	int		count;
	char	*str;

	i = 0;
	while (cmd->argv[i])
	{
		j = 0;
		count = 0;
		while (cmd->argv[i]->str[j])
		{
			if (cmd->argv[i]->str[j] == '\'' || cmd->argv[i]->str[j] == '\"')
				count++;
			j++;
		}
		str = ft_malloc(sizeof(char) * (ft_strlen(cmd->argv[i]->str) - count + 1));
		j = 0;
		count = 0;
		while (cmd->argv[i]->str[j])
		{
			if (cmd->argv[i]->str[j] != '\'' && cmd->argv[i]->str[j] != '\"')
			{
				str[count] = cmd->argv[i]->str[j];
				count++;
			}
			j++;
		}
		str[count] = '\0';
		free(cmd->argv[i]);
		cmd->argv[i]->str = str;
		i++;
	}
}

int	insert_var(t_data *shell, char **arg, int start)
{
	char	*key;
	char	*out;
	char	*value;
	int		i;

	i = 1;
	if ((*arg)[start + i] == '?')
	{
		value = ft_itoa(shell->code_error);
		out = ft_substr(*arg, 0, start);
		out = ft_str_appnd(out, value, 1, 1);
		out = ft_str_appnd(out, *arg + start + i + 1, 1, 0);
		free(*arg);
		*arg = out;
		return (1);
	}
	while ((*arg)[start + i] && ft_isalnum((*arg)[start + i]))
		i++;
	key = malloc(sizeof(char) * i);
	ft_strlcpy(key, (*arg) + start + 1, i);
	value = env_get(shell, key);
	out = ft_substr(*arg, 0, start);
	out = ft_str_appnd(out, value, 1, 1);
	out = ft_str_appnd(out, *arg + start + i, 1, 0);
	free(key);
	free(*arg);
	*arg = out;
	return (i - 1);
}
