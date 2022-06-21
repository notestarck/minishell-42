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

static void	init_env(t_data *shell, char **env)
{
	int	i;

	i = 0;
	(void)shell;
	while (env[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1)); //penser a free
	if (shell->env == NULL)
		perror("error : malloc env");
	i = 0;
	while (env[i])
	{
		shell->env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strlcpy(shell->env[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
}

static void	launch_shell(t_data *shell)
{
	char	*tmp;
	char	*prompt;

	prompt = ft_str_appnd(env_get(shell, "USER"), "@", 1, 0);
	prompt = ft_str_appnd(prompt, env_get(shell, "NAME"), 1, 1);
	prompt = ft_str_appnd(prompt, ": ", 1, 0);
	prompt = ft_str_appnd(prompt, env_get(shell, "PWD"), 1, 1);
	prompt = ft_str_appnd(prompt, " minishell $> ", 1, 0);
	shell->ret_prompt = readline(prompt);
	free(prompt);
	if (*shell->ret_prompt != '\0')
		add_history(shell->ret_prompt);
}

static t_data	*init_shell(void)
{
	t_data	*shell;

	shell = malloc(sizeof(t_data)); //ret erreur
	shell->builtins[0] = "echo";
	shell->builtins[1] = "cd";
	shell->builtins[2] = "pwd";
	shell->builtins[3] = "export";
	shell->builtins[4] = "unset";
	shell->builtins[5] = "env";
	shell->builtins[6] = "exit"; 
	shell->builtins[7] = NULL;
	shell->pid = 0;
	init_env_path(shell);
	return (shell);
}

//Quand on utilise des builtins, le message de fin s'affiche bizarrement
//Les buitlins ne returnent surement pas, donc plusieurs fork écrive en meme temps

void	quit_mini(int sig)
{
	ft_printf("\n");
	clear_history();
	ft_printf("Farewell\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argc;
	(void)argv;
	signal(2, quit_mini);
	shell = init_shell();
	//char *in = malloc(sizeof(char) * 100);
	//read(0, in, 100);
	//ft_printf("%d\n", *in);
	if (shell->pid == 0)
		init_env(shell, env);
	while (42)
	{
		launch_shell(shell);
		shell->cmd = parse_prompt(shell);
		check_syntax(shell);
		if (*shell->ret_prompt != '\0')
		{
			if (check_error(shell->cmd))
			{
				if (find_cmd(shell))
					run_cmd(shell);
			}
			free_cmd(shell->cmd);
		}
		free(shell->ret_prompt);
	}
}
