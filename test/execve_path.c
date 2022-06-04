/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 07:33:36 by estarck           #+#    #+#             */
/*   Updated: 2022/06/04 08:58:26 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

void	exe_shell(char *argv, char **envp)
{
	pid_t	child;
	char	*my_argv[4];
	char	*my_envp[3];

	my_argv[0] = "/bin/bash";
	my_argv[1] = "-c";
	my_argv[2] = argv;
	my_argv[3] = NULL;
	my_envp[0] = "PATH=./bltin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	my_envp[1] = NULL;
	child = fork();
	if (child == 0)
	{
		execve("/bin/bash", my_argv, my_envp);
		perror ("error : fork");
	}
	else
	{
		wait(NULL);
	}
}

char	*init_shell(void)
{
	char	*argv;

	argv = readline("mini_shell $ ");
	add_history(argv);
	return (argv);
}

int	main(int argc, char **argv, char **envp)
{
	char	*ret_prompt;

	while (42)
	{
		ret_prompt = init_shell();
		exe_shell(ret_prompt, envp);
	}
}