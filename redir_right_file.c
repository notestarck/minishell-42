/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_right_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:15:17 by estarck           #+#    #+#             */
/*   Updated: 2022/05/27 10:36:14 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(void)
{
	int			fd;
	pid_t		child;
	char 		*filename;
	char		*cmd1;
	char		*args1[3];
	
	filename = "./test.out";

	cmd1 = "/bin/ls";
	args1[0] = "ls";
	args1[1] = "-laF";
	args1[2] = NULL;
	
	fd = open(filename, O_WRONLY | O_CREAT);
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
		dup2(fd, STDOUT_FILENO);
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
