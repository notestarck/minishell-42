/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:35:52 by reclaire          #+#    #+#             */
/*   Updated: 2022/07/01 13:32:20 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_data *shell, t_lst *cmd)
{
	if (cmd->argv[1] != NULL)
		env_del(shell, cmd->argv[1]->str);
	return ;
}
