/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:43:30 by estarck           #+#    #+#             */
/*   Updated: 2022/06/14 17:31:16 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_blt(t_data *shell, t_lst *cmd)
{
	if (cmd->built == 1)
		exec_cd(shell, cmd);
	else if (cmd->built == 2)
		exec_pwd(shell, cmd);
	return ;
}
