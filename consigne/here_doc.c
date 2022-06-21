/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:33:56 by estarck           #+#    #+#             */
/*   Updated: 2022/06/21 17:44:43 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredocs(t_data *shell, t_lst *cmd)
{
	int		fd;
	char	*buf;

	fd = open(cmd->tmpfile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	buf = readline("heredocs>>> ");
	while (1)
	{
		if (ft_strcmp(buf, cmd->heredocsfd[0]) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		buf = readline("heredocs>>> ");
	}
	free(buf);
	close(fd);
	mem->exec_loop->fdin = open(mem->tmpfile, O_RDONLY, 0777);
	dup2(mem->exec_loop->fdin, STDIN_FILENO);
	close(mem->exec_loop->fdin);
}