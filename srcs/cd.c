/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:11:55 by estarck           #+#    #+#             */
/*   Updated: 2022/06/14 17:54:14 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_data *shell, t_lst *cmd)
{
	int		i;
	char	n_pwd[256];
	char	o_pwd[256];
	
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp("PWD", shell->env[i], 3))
		{
			getcwd(o_pwd, ft_strlen(shell->env[i]));
			free(shell->env[i]);
			chdir(cmd->argv[1]);
			shell->env[i] = ft_strjoin("PWD=", getcwd(n_pwd, 256));
		}
		if (!ft_strncmp("OLDPWD", shell->env[i], 6))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", o_pwd);
		}
		i++;
	}
	return ;
}
