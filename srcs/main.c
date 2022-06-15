/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:39:17 by estarck           #+#    #+#             */
/*   Updated: 2022/06/14 17:30:55 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_strlcpy(shell->env[i], env[i], ft_strlen(env[i]));
		i++;
	}
}

static void	launch_shell(t_data *shell)
{
	shell->ret_prompt = readline("minishell $> ");
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
	//shell->builtins[5] = "env";
	shell->builtins[6] = "exit";
	shell->builtins[7] = NULL;
	init_env_path(shell);
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argc;
	(void)argv;
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
	}
}
