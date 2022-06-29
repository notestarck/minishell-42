/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_right.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:38:18 by estarck           #+#    #+#             */
/*   Updated: 2022/06/28 15:27:02by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_args(t_lst *cmd)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	while (*cmd->argv[i] != '>')
		i++;
	ret = malloc(sizeof(char *) * i + 1);
	if (ret == NULL)
		return (perror("error : malloc find_args"), NULL);
	while (j < i)
	{
		ret[j] = malloc(sizeof(char) * ft_strlen(cmd->argv[j]) + 1);
		if (ret[j] == NULL)
			return (perror("error : malloc"), NULL);
		ft_strlcpy(ret[j], cmd->argv[j], ft_strlen(cmd->argv[j]) + 1);
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

static char	*find_dir(t_lst *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (*cmd->argv[i] == '>')
			return (cmd->argv[i + 1]);
		i++;
	}
	return (NULL);
}

static void	exec_child(t_data *shell, t_lst *cmd, char **args, int fd)
{
	if (cmd->built == 9)
	{
		fd_manager2(shell, cmd, fd);
		execve(cmd->p_cmd, args, shell->env);
		shell->code_error = errno;
		return (perror("minishell"));
	}
	else if (cmd->built != 9)
	{
		fd_manager2(shell, cmd, fd);
		exec_blt(shell, cmd);
		exit (0);
	}
}

void	d_right(t_data *shell, t_lst *cmd)
{
	int		fd;
	char	*filename;
	char	**args;

	filename = find_dir(cmd);
	args = find_args(cmd);
	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
		return (perror ("error : open dir"));
	g_pid = fork();
	if (g_pid < 0)
		return (close (fd), perror("error : fork d_right"));
	else if (g_pid == 0)
		exec_child(shell, cmd, args, fd);
	else
	{
		wait(NULL);
		close(fd);
	}
	free(args);
}
