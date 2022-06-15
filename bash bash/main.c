/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:57:56 by estarck           #+#    #+#             */
/*   Updated: 2022/06/15 16:54:16 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

static void init_fork(char **envp)
{
	pid_t	pid;
	char	*sh[4];

	sh [0] = "/bin/bash";
	sh [1] = "-c";
	sh [2] = "bash --rcfile  ./sshrc.c";
	sh [3] = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/sh", sh, envp);
	else
		wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	init_fork(envp);
	return (0);
}