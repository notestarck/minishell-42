/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:11:55 by estarck           #+#    #+#             */
/*   Updated: 2022/06/15 16:59:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <sys/types.h>

void	exec_cd(t_data *shell, t_lst *cmd)
{
	char	*tmp;
	char	new[PATH_MAX];


	if (!ft_strncmp(cmd->argv[1], "--", 2) || !ft_strncmp(cmd->argv[1], "~", 1))
	{
		free(cmd->argv[1]);
		cmd->argv[1] = env_get(shell, "HOME");
	}
	else if (!ft_strncmp(cmd->argv[1], "-", 1))
	{
		free(cmd->argv[1]);
		cmd->argv[1] = env_get(shell, "OLDPWD");
	}
	ft_printf("			%s\n", cmd->argv[1]);
	tmp = env_get(shell, "PWD");
	env_set(shell, "OLDPWD", tmp);
	free(tmp);
	chdir(cmd->argv[1]);
	getcwd(new, PATH_MAX);
	env_set(shell, "PWD", new);
	return ;
}
