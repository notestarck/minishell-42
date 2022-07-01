/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:11:55 by estarck           #+#    #+#             */
/*   Updated: 2022/07/01 13:40:45 by reclaire         ###   ########.fr       */
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

	if (cmd->next != NULL)
		return ;
	if (cmd->argv[1] == NULL || !ft_strncmp(cmd->argv[1]->str, "--", 2)
		|| !ft_strncmp(cmd->argv[1]->str, "~", 1))
		tmp2 = env_get(shell, "HOME");
	else if (!ft_strncmp(cmd->argv[1]->str, "-", 1))
		tmp2 = env_get(shell, "OLDPWD");
	else
		tmp2 = cmd->argv[1]->str;
	tmp = env_get(shell, "PWD");
	env_set(shell, "OLDPWD", tmp);
	free(tmp);
	if (chdir(tmp2) == -1)
	{
		perror("cd");
		shell->code_error = errno;
		return ;
	}
	getcwd(new, PATH_MAX);
	env_set(shell, "PWD", new);
	return ;
}
