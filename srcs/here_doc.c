/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:33:56 by estarck           #+#    #+#             */
/*   Updated: 2022/06/23 14:14:47 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_cat(t_lst *cmd)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 2);
	argv[0] = malloc(sizeof(char) * 4);
	argv[1] = malloc(sizeof(char) * 1);
	argv[0] = "cat";
	argv[1] = NULL;
	cmd->argv = argv;
}

static void	repars_heredocs(t_lst *cmd)
{
	char	**argv;
	int		i;

	i = 0;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i], "<<", 3))
		i++;
	if (i == 0)
	{
		write_cat(cmd);
		return ;
	}
	argv = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i], "<<", 3))
	{
		argv[i] = cmd->argv[i];
		i++;
	}
	argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = argv;
}

static int	find_eof(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_strcmp("<<", &argv[i][0]))
			break ;
		i++;
	}
	return (i);
}

static void	run_heredocs(t_lst *cmd)
{
	int		fd;
	char	*buf;
	int		i;

	buf = readline("heredoc> ");
	fd = open(cmd->tmpfile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	i = find_eof(cmd->argv);
	while (1)
	{
		if (ft_strcmp(buf, cmd->argv[i + 1]) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		buf = readline("heredoc> ");
	}
	free(buf);
	close(fd);
	cmd->pipefd[READ] = open(cmd->tmpfile, O_RDONLY, 0777);
	unlink(cmd->tmpfile);
	dup2(cmd->pipefd[READ], STDIN_FILENO);
	close(cmd->pipefd[READ]);
}

void	init_heredoc(t_lst *cmd)
{
	run_heredocs(cmd);
	repars_heredocs(cmd);
}