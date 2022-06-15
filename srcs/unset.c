/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:35:52 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/15 20:50:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_data *shell, t_lst *cmd)
{
	env_del(shell, cmd->argv[1]);
	ft_printf("FDTWAUVHBOIDWUAB\n");
	return ;
}
