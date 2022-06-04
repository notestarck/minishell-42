/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:09:00 by estarck           #+#    #+#             */
/*   Updated: 2022/06/04 13:44:42 by estarck          ###   ########.fr       */
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
	shell->pwd = getenv("PATH");
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
		ft_free(shell);

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
		if (launch_mshell(shell) == -1)
			break ;
	}
	//faire les derniers free si besoin genre t_shell
	return (0);
}