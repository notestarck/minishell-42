/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:39:17 by estarck           #+#    #+#             */
/*   Updated: 2022/06/16 13:21:22 by estarck          ###   ########.fr       */
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
	char	*usr;
	char	*name;
	char	*pwd;

	usr = env_get(shell, "USER");
	name = env_get(shell, "NAME");
	pwd = env_get(shell, "PWD");
	prompt = ft_str_appnd(usr, "@", 1, 0);
	tmp = ft_str_appnd(prompt, name, 1, 1);
	prompt = ft_str_appnd(tmp, ":", 1, 0);
	tmp = ft_str_appnd(prompt, pwd, 1, 1);
	prompt = ft_str_appnd(tmp, " $> ", 1, 0);
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
	init_env_path(shell);
	return (shell);
}

//Quand on utilise des builtins, le message de fin s'affiche bizarrement
//Les buitlins ne returnent surement pas, donc plusieurs fork écrive en meme temps

void	quit(int sig)
{
	ft_printf("\n");
	rl_clear_history();
	ft_printf("Farewell\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argc;
	(void)argv;
	signal(2, quit);
	shell = init_shell();
	init_env(shell, env);
	while (42)
	{
		launch_shell(shell);
		shell->cmd = parse_prompt(shell);
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
