/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:00:51 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 17:44:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	exec_export(t_data *shell, t_lst *cmd)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(cmd->argv[1]->str, '=');
	while (cmd->argv[1]->str[i])
	{
		if (!ft_strncmp(&cmd->argv[1]->str[i], "=", 1))
		{
			break ;
		}
		i++;
	}
	env_set(shell, tmp[0], &cmd->argv[1]->str[i + 1]);
	free_tmp(tmp);
}
