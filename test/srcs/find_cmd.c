/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:39:52 by estarck           #+#    #+#             */
/*   Updated: 2022/05/30 09:39:03y estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//verifie si le path est valide
static int	valid_path(char *av)
{
	struct stat	buf;

	if (stat(av, &buf) == -1)
	{
		perror("error stat");
		return (0);
	}
	else
		return (1);
}

//cherche la cmd dans les path de l'env
static char	*find_path(char **env_path, char *cmd)
{
	DIR				*dir;
	struct dirent	*dp;

	while (*env_path != NULL)
	{
		dir = opendir(*env_path);
		if (dir == NULL)
			perror ("error opendir");
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strncmp(dp->d_name, cmd, ft_strlen(cmd) + 1))
			{
				closedir(dir);
				return (ft_strjoin(ft_strjoin(*env_path, "/"), cmd)) ;
			}
			dp = readdir(dir);
		}
		closedir(dir);
		env_path++;
	}
	return (0);
}

int	find_cmd(t_data *shell)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		if (ft_strchr(tmp->argv[0], 47))
		{
			if (valid_path(tmp->argv[0]))
			{
				perror("error cmd");
				return (0);
			}
			tmp->p_cmd = tmp->argv[0];
		}
		else
		{
			tmp->p_cmd = find_path(shell->env_path, tmp->argv[0]); // Penser a free
			if (tmp->p_cmd == NULL)
			{
				perror("error cmd");
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
