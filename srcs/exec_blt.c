/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:43:30 by estarck           #+#    #+#             */
/*   Updated: 2022/06/16 16:54:18 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_blt(t_data *shell, t_lst *cmd)
{
	if (cmd->built == CD)
		exec_cd(shell, cmd);
	else if (cmd->built == PWD)
		exec_pwd(shell, cmd);
	else if (cmd->built == ENV)
		exec_env(shell);
	else if (cmd->built == EXPORT)
		exec_export(shell, cmd);
	else if (cmd->built == UNSET)
		exec_unset(shell, cmd);
	else if (cmd->built == EXIT)
		return ;
	return ;
}
