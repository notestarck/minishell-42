/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:39:17 by estarck           #+#    #+#             */
/*   Updated: 2022/06/09 12:21:06 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	launch_shell(t_data *shell)
{
	shell->ret_prompt = readline("minishell $> ");
	add_history(shell->ret_prompt);
}

static t_data	*init_shell(char **env)
{
	t_data	*shell;

	shell = malloc(sizeof(t_data)); //ret erreur
	shell->env = env;
	init_env_path(shell);
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(env);
	while (42)
	{
		launch_shell(shell);
		shell->cmd = parse_prompt(shell);
		if (*shell->ret_prompt != '\0')
		{
			if (check_error(shell->cmd))
			{
				if (find_cmd(shell))
					exec_cmd(shell);
			}
			free_cmd(shell->cmd);
		}
	}
}
