/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:35:52 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/07 19:25:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_data *shell, t_lst *cmd)
{
	if (cmd->argv[1] != NULL)
		env_del(shell, cmd->argv[1]->str);
	return ;
}
