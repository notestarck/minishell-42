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
		perror(strerror(ENOTDIR));
		return (ENOTDIR);
	}
	else
		return (0);
}

//cherche la cmd dans les path de l'env
static char	*find_path(char **env_path, char *cmd)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*tmp;
	char			*out;
	char			*path;

	while (*env_path != NULL)
	{
		dir = opendir(*env_path);
		if (access(*env_path, R_OK))
		{
			closedir(dir);
			env_path++;
			continue ;
		}
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strncmp(dp->d_name, cmd, ft_strlen(cmd) + 1))
			{
				path = ft_str_appnd(*env_path, "/", 0, 0);
				path = ft_str_appnd(path, dp->d_name, 1, 0);
				if (access(path, X_OK))
				{
					ft_printf("-minishell: %s/%s: Permission denied.\n",
						*env_path, dp->d_name);
					dp = readdir(dir);
					continue ;
				}
				closedir(dir);
				tmp = ft_strjoin(*env_path, "/");
				out = ft_strjoin(tmp, cmd);
				free(tmp);
				return (out);
			}
			dp = readdir(dir);
		}
		//free(dp);
		closedir(dir);
		env_path++;
	}
	ft_printf("-minishell: %s: command not found\n", cmd);
	return (0);
}

int	find_cmd(t_data *shell)
{
	t_lst	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		if (init_blt(shell, tmp) == -1)
		{
			if (ft_strchr(tmp->argv[0], 47))
			{
				if (valid_path(tmp->argv[0])) //message d'erreur si le ptah n'est pas valide
					return (0);
				tmp->p_cmd = malloc(sizeof(char) * (ft_strlen(tmp->argv[0]) + 1));
				ft_strlcpy(tmp->p_cmd, tmp->argv[0], ft_strlen(tmp->argv[0]) + 1);
			}
			else if (ft_strchr(&tmp->argv[0][0], 60) && ft_strchr(&tmp->argv[0][1], 60))
			{
				tmp->p_cmd = find_path(shell->env_path, "cat");
				printf("%s\n", tmp->p_cmd);
			}
			else
			{
				tmp->p_cmd = find_path(shell->env_path, tmp->argv[0]); // Penser a free
				if (tmp->p_cmd == NULL)
					return (0);
			}
			tmp->built = 9;
		}
		tmp = tmp->next;
	}
	return (1);
}
