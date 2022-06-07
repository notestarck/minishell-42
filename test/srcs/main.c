/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:09:00 by estarck           #+#    #+#             */
/*   Updated: 2022/06/07 17:35:58 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shell	*init_mshell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		perror("error : init shell");
		exit (0);
	}
	shell->env = envp;
	shell->pwd = getenv("PWD");
	shell->builtins[0] = "echo";
	shell->builtins[1] = "cd";
	shell->builtins[2] = "pwd";
	shell->builtins[3] = "export";
	shell->builtins[4] = "unset";
	shell->builtins[5] = "env";
	shell->builtins[6] = "exit";
	shell->builtins[7] = NULL;
	return (shell);
}

static void	display_prompt(t_shell *shell)
{
	shell->ret_prompt = readline("mmini_shell $ ");
	if (shell->ret_prompt == NULL)
	{
		ft_perror(NULL, shell, 1);
		exit (0);
	}
	add_history(shell->ret_prompt);
}

static int	launch_mshell(t_shell *shell)
{
	int	ret;

	ret = 0;
	(void)shell;
	if (parsing(shell))
	{
		init_cmd(shell);
		exec_all(shell);
		ft_free(shell);
	}

	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_mshell(envp);
	while (42)
	{
		display_prompt(shell);
		if (launch_mshell(shell))
			break ;
	}
	//faire les derniers free si besoin genre t_shell
	return (0);
}