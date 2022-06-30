/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_left.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:41:51 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 17:56:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	**find_args(t_lst *cmd)
{
	int		i;
	int		j;
	t_arg	**ret;

	i = 0;
	j = 0;
	while (*(cmd->argv[i]->str) != '<')
		i++;
	ret = ft_malloc(sizeof(t_arg *) * (i + 1));
	while (j < i)
	{
		ret[j] = cmd->argv[i];
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
		if (*(cmd->argv[i]->str) == '<')
			return (cmd->argv[i + 1]->str);
		i++;
	}
	return (NULL);
}

void	s_left(t_data *shell, t_lst *cmd)
{
	int		fd;
	char	*filename;
	t_arg	**args;

	filename = find_dir(cmd);
	args = find_args(cmd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror ("error : open dir"));
	g_pid = fork();
	if (g_pid < 0)
		return (close (fd), perror("error : fork s_left"));
	else if (g_pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		execve(cmd->p_cmd, t_arg_to_char(args), shell->env);
		perror("minishell");
	}
	else
	{
		wait(NULL);
		close(fd);
	}
	free(args);
}
