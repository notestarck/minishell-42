/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:59:18 by estarck           #+#    #+#             */
/*   Updated: 2022/06/28 17:47:59 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_dchar(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_cmd(t_lst *cmd)
{
	t_lst	*tmp;

	tmp = cmd;
	while (tmp)
	{
		free_dchar(cmd->argv);
		if (tmp->p_cmd)
			free(tmp->p_cmd);
		cmd = cmd->next;
		free(tmp);
		tmp = cmd;
	}
}
