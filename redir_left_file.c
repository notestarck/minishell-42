/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_left_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:15:17 by estarck           #+#    #+#             */
/*   Updated: 2022/05/27 10:20:52 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int			fd;
	pid_t		child;
	char 		*filename;
	char		*cmd1;
	char		*args1[3];
	
	if (argc != 3)
	{
		perror("error arguments");
		return (-1);
	}
	filename = argv[2];

	cmd1 = "/usr/bin/grep";
	args1[0] = "grep";
	args1[1] = argv[1];
	args1[2] = NULL;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("error");
		return (-1);
	}

	child = fork();
	if (child == -1)
	{
		close(fd);
		perror("error");
		return (-1);
	}
	if (child == 0)
	{
		dup2(fd, STDIN_FILENO);
		execve(cmd1, args1, NULL);
		perror ("error");
	}
	else
	{
		wait(NULL);
		close(fd);
	}
	return (0);
}
