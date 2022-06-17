/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:05:56 by estarck           #+#    #+#             */
/*   Updated: 2022/06/17 17:15:32 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_op(t_data *shell, t_lst *cmd)
{
	if (cmd->sep == S_LEFT)
		s_left(shell, cmd);
	else if (cmd->sep == S_RIGHT)
		s_right(shell, cmd);
	else if (cmd->sep == D_RIGHT)
		d_right(shell, cmd);
}
