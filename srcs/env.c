/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:53:35 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/15 20:58:44 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
	return ;
}
