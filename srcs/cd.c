/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:11:55 by estarck           #+#    #+#             */
/*   Updated: 2022/06/15 16:19:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <sys/types.h>

void	exec_cd(t_data *shell, t_lst *cmd)
{
	char	*tmp;
	int		size;

	tmp = env_get(shell, "PWD");
	env_set(shell, "OLDPWD", tmp);
	size = ft_strlen(cmd->argv[1]) + ft_strlen(tmp);
	free(tmp);
	tmp = malloc(sizeof(char) * size);
	chdir(cmd->argv[1]);
	getcwd(tmp, size);
	env_set(shell, "PWD", tmp);
	free(tmp);
	return ;
}
