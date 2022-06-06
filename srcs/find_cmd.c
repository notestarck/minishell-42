/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:05:01 by estarck           #+#    #+#             */
/*   Updated: 2022/06/06 10:16:37 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char **path, char *cmd)
{
	DIR				*dir;
	struct dirent	*dp;

	while (*path != NULL)
	{
		dir = opendir(*path);
		if (dir == NULL)
			perror ("error opendir");
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strncmp(dp->d_name, cmd, ft_strlen(cmd) + 1))
			{
				closedir(dir);
				return (ft_strjoin(ft_strjoin(*path, "/"), cmd));
			}
			dp = readdir(dir);
		}
		closedir(dir);
		(path)++;
	}
	return (0);
}

void	find_cmd(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		tmp->cmd = find_path(shell->path, tmp->argv[0]);
		tmp = tmp->next;
	}
}