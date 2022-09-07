/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:10:03 by estarck           #+#    #+#             */
/*   Updated: 2022/09/07 16:59:14 by estarck          ###   ########.fr       */
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
			{
				j += insert_var(shell, cmd->argv[i], j);
			}
				j++;
		}
		i++;
	}
}

void	insert_var_inter(t_data *shell, char **arg, int start)
{
	char	*out;
	char	*value;
	int		i;

	i = 1;
	value = ft_itoa(shell->code_error);
	out = ft_substr(*arg, 0, start);
	out = ft_str_appnd(out, value, 1, 1);
	out = ft_str_appnd(out, *arg + start + i + 1, 1, 0);
	free(*arg);
	*arg = out;
}
