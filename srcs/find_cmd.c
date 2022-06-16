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
		perror("error cmd");
		return (1);
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

	while (*env_path != NULL)
	{
		dir = opendir(*env_path);
		//Une erreur opendir n'est pas grave, ca veut juste dire qu'on a pas les droits d'acceder au dossier
		//Donc on la laisse passer, et on continue
		//La fonction access nous permet de verifier proprement qu'on a tout les droits
		//if (dir == NULL)
		//	perror ("Error opendir");
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
				if (access(dp->d_name, X_OK))
				{
					ft_printf("-minishell: %s%s: Permission denied.\n", *env_path, dp->d_name);
					dp = readdir(dir);
					continue;
				}
				closedir(dir);
				tmp = ft_strjoin(*env_path, "/");
				out = ft_strjoin(tmp, cmd);
				free(tmp);
				return (out) ;
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
				if (valid_path(tmp->argv[0]))
					return (0);
				tmp->p_cmd = tmp->argv[0];
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
