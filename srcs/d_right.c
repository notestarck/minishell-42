/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_right.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:38:18 by estarck           #+#    #+#             */
/*   Updated: 2022/06/17 17:06:56 by estarck          ###   ########.fr       */
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
		perror("error : malloc find_args");
	while (j < i)
	{
		ret[j] = malloc(sizeof(char) * ft_strlen(cmd->argv[j]) + 1);
		if (ret[j] == NULL)
			perror("error: malloc");
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

void	d_right(t_data *shell, t_lst *cmd)
{
	int		fd;
	pid_t	pid;
	char	*filename;
	char	**args;

	filename = find_dir(cmd);
	args = find_args(cmd);
	fd = open(filename, O_APPEND | O_CREAT);
	if (fd == -1)
	{
		perror ("error : open dir");
	}
	pid = fork();
	if (pid < 0)
	{
		close (fd);
		perror("error : fork s_right");
	}
	else if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(cmd->p_cmd, args, shell->env);
		perror("error : ");
	}
	else
	{
		wait(NULL);
		close(fd);
	}
	free(args);
}