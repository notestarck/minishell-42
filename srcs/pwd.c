/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:13:48 by estarck           #+#    #+#             */
/*   Updated: 2022/06/23 21:00:40 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_data *shell, t_lst *cmd)
{
	int	i;

	while (cmd->argv[i])
		i++;
	if (i != 1)
	{
		ft_printf("pwd: too many arguments\n");
		return ;
	}
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "PWD", 3))
			printf("%s\n", (shell->env[i] + 4));
		i++;
	}
	return ;
}