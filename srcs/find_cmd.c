/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:39:52 by estarck           #+#    #+#             */
/*   Updated: 2022/07/01 14:59:33 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path2(DIR *dir, struct dirent *dp, char **env_path, char *cmd)
{
	char			*tmp;
	char			*out;
	char			*path;

	path = ft_str_appnd(*env_path, "/", 0, 0);
	path = ft_str_appnd(path, dp->d_name, 1, 0);
	if (access(path, X_OK))
	{
		ft_printf("-minishell: %s/%s: Permission denied.\n",
			*env_path, dp->d_name);
		return (NULL);
	}
	closedir(dir);
	tmp = ft_strjoin(*env_path, "/");
	out = ft_strjoin(tmp, cmd);
	free(tmp);
	free(path);
	return (out);
}

static int	check_acces(char **env_path, DIR *dir)
{
	if (access(*env_path, R_OK))
	{
		closedir(dir);
		env_path++;
		return (1);
	}
	return (0);
}

//cherche la cmd dans les path de l'env
static char	*find_path(t_data *shell, char **env_path, char *cmd)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*out;

	while (*env_path != NULL)
	{
		dir = opendir(*env_path);
		if (check_acces(env_path, dir))
			continue ;
		dp = readdir(dir);
		while (dp)
		{
			if (!ft_strncmp(dp->d_name, cmd, ft_strlen(cmd) + 1))
			{
				out = find_path2(dir, dp, env_path, cmd);
				if (out != NULL)
					return (out);
			}
			dp = readdir(dir);
		}
		closedir(dir);
		env_path++;
	}
	shell->code_error = COMMAND_NOT_FOUND;
	return (ft_printf("-minishell: %s: command not found\n", cmd), NULL);
}

int	find_cmd_2(t_data *shell, t_lst *tmp)
{
	if (init_blt(shell, tmp) == -1)
	{
		if (ft_strchr(tmp->argv[0]->str, 47))
		{
			if (valid_path(shell, tmp->argv[0]->str))
				return (0);
			tmp->p_cmd = malloc(sizeof(char) * \
				(ft_strlen(tmp->argv[0]->str) + 1));
			ft_strlcpy(tmp->p_cmd, tmp->argv[0]->str, \
				ft_strlen(tmp->argv[0]->str) + 1);
		}
		else if (ft_strchr(&tmp->argv[0]->str[0], 60) && \
			ft_strchr(&tmp->argv[0]->str[1], 60))
			tmp->p_cmd = find_path(shell, shell->env_path, "cat");
		else
		{
			tmp->p_cmd = find_path(shell, shell->env_path, tmp->argv[0]->str);
			if (tmp->p_cmd == NULL)
				return (0);
		}
		tmp->built = 9;
	}
	return (1);
}

int	find_cmd(t_data *shell)
{
	t_lst	*tmp;

	init_env_path(shell);
	tmp = shell->cmd;
	while (tmp)
	{
		if (!find_cmd_2(shell, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
