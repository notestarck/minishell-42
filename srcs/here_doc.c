/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:33:56 by estarck           #+#    #+#             */
/*   Updated: 2022/06/22 17:53:26 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredocs(t_data *shell, t_lst *cmd)
{
	pid_t	pid;
	char	*argv[2];

	argv[0] = cmd->argv[0];
	argv[1] = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("error : exec_heredocs");
	}
	else if (pid == 0)
	{
		execve(cmd->p_cmd, argv, shell->env);
	}
	else
		wait (NULL);
}

int	find_eof(char **argv)
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

void	run_heredocs(t_data *shell, t_lst *cmd)
{
	int		fd;
	char	*buf;
	int		i;

	fd = open(cmd->tmpfile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	buf = readline("heredoc> ");
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
