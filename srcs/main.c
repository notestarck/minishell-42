/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:39:17 by estarck           #+#    #+#             */
/*   Updated: 2022/06/17 10:0 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	g_pid = 0;

static void	launch_shell(t_data *shell)
{
	char	*prompt;

	prompt = ft_str_appnd(env_get(shell, "USER"), "@", 1, 0);
	prompt = ft_str_appnd(prompt, env_get(shell, "NAME"), 1, 1);
	prompt = ft_str_appnd(prompt, ": ", 1, 0);
	prompt = ft_str_appnd(prompt, env_get(shell, "PWD"), 1, 1);
	prompt = ft_str_appnd(prompt, " minishell $> ", 1, 0);
	shell->ret_prompt = readline(prompt);
	free(prompt);
	if (shell->ret_prompt && *shell->ret_prompt != '\0')
		add_history(shell->ret_prompt);
	if (!shell->ret_prompt)
	{
		shell->code_error = INPUT_ERROR;
		quit_mini(shell);
	}
}

static t_data	*init_shell(void)
{
	t_data	*shell;

	shell = malloc(sizeof(t_data));
	shell->builtins[0] = "echo";
	shell->builtins[1] = "cd";
	shell->builtins[2] = "pwd";
	shell->builtins[3] = "export";
	shell->builtins[4] = "unset";
	shell->builtins[5] = "env";
	shell->builtins[6] = "exit";
	shell->builtins[7] = NULL;
	shell->seed = 87634;
	shell->env_path = NULL;
	shell->code_error = 0;
	return (shell);
}

void	quit_mini(t_data *shell)
{
	free_all(shell);
	ft_printf("\n");
	ft_printf("Farewell\n");
	exit(shell->code_error);
}

void	sig(int sig)
{
	if (g_pid)
		return ;
	else if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_printf("  \b\b");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argc;
	(void)argv;
	g_pid = 0;
	signal(SIGINT, sig);
	signal(SIGQUIT, sig);
	shell = init_shell();
	init_env(shell, env);
	while (42)
	{
		launch_shell(shell);
		parse_prompt(shell);
		if (*shell->ret_prompt != '\0')
		{
			if (!check_error(shell, shell->cmd))
			{
				if (find_cmd(shell))
					run_cmd(shell);
			}
			free_cmd(shell->cmd);
		}
		free(shell->ret_prompt);
	}
}
