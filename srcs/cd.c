/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:11:55 by estarck           #+#    #+#             */
/*   Updated: 2022/06/23 16:46:17 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <sys/types.h>

void	exec_cd(t_data *shell, t_lst *cmd)
{
	char	*tmp;
	char	*tmp2;
	char	new[PATH_MAX];

	if (shell->nbr_cmd != 1)
		return ;
	if (cmd->argv[1] == NULL || !ft_strncmp(cmd->argv[1], "--", 2) || !ft_strncmp(cmd->argv[1], "~", 1))
		tmp2 = env_get(shell, "HOME");
	else if (!ft_strncmp(cmd->argv[1], "-", 1))
		tmp2 = env_get(shell, "OLDPWD");
	else
		tmp2 = cmd->argv[1];
	tmp = env_get(shell, "PWD");
	env_set(shell, "OLDPWD", tmp);
	free(tmp);
	chdir(tmp2);
	getcwd(new, PATH_MAX);
	env_set(shell, "PWD", new);
	return ;
}
