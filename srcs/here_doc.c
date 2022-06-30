/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:33:56 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 18:51:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_cat(t_lst *cmd)
{
	t_arg	**argv;

	argv = malloc(sizeof(t_arg *) * 2);
	argv[0] = ft_malloc(sizeof(t_arg));
	argv[0]->str = ft_strdup("cat");
	argv[1] = NULL;
	cmd->argv = argv;
}

static void	repars_heredocs(t_lst *cmd)
{
	t_arg	**argv;
	int		i;

	i = 0;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i]->str, "<<", 3))
		i++;
	if (i == 0)
	{
		write_cat(cmd);
		return ;
	}
	argv = ft_malloc(sizeof(t_arg *) * (i + 1));
	i = 0;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i]->str, "<<", 3))
	{
		argv[i] = cmd->argv[i];
		i++;
	}
	argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = argv;
}

static int	find_eof(t_arg **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_strcmp("<<", argv[i]->str))
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
	while (42)
	{
		if (ft_strcmp(buf, cmd->argv[i + 1]->str) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		buf = readline("heredoc> ");
	}
	free(buf);
	close(fd);
	cmd->pipefd[READ] = open(cmd->tmpfile, O_RDONLY, 0777);
	unlink(cmd->tmpfile);
}

void	init_heredoc(t_lst *cmd)
{
	run_heredocs(cmd);
	repars_heredocs(cmd);
}
