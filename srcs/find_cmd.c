/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:05:01 by estarck           #+#    #+#             */
/*   Updated: 2022/06/04 14:12:06 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void find_path(t_shell *shell, t_cmd *cmd)
{
	DIR				*dir;
	struct dirent	*dp;

	while (*shell->env != NULL)
	{
		dir = opendir(*shell->env);
		if (dir == NULL)
			perror ("error opendir");
		dp = readdir(dir);
		
	}
}

void	find_cmd(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		
		tmp = tmp->next;
	}
}