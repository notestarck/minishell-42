/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:13:48 by estarck           #+#    #+#             */
/*   Updated: 2022/06/14 13:17:42 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_data *shell, t_lst *cmd)
{
	int	i;

	i = 0;
	(void)cmd;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "PWD", 3))
			printf("%s\n", (shell->env[i] + 4));
		i++;
	}
	return ;
}