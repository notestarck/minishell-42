/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:35:52 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/16 17:29:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_data *shell, t_lst *cmd)
{
	ft_printf("%p\n", shell->env);
	env_del(shell, cmd->argv[1]);
	ft_printf("%p\n", shell->env);
	return ;
}
