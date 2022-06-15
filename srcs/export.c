/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:00:51 by estarck           #+#    #+#             */
/*   Updated: 2022/06/15 17:36:59 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_tmp(char **tmp)
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
	tmp = ft_split(cmd->argv[1], '=');
	while (cmd->argv[1][i])
	{
		if (!ft_strncmp(&cmd->argv[1][i], "=", 1))
		{
			printf("%d\n", i);
			break ;
		}
		i++;
	}
	env_set(shell, tmp[0], &cmd->argv[1][i + 1]);
	free_tmp(tmp);
}
