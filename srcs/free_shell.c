/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:59:18 by estarck           #+#    #+#             */
/*   Updated: 2022/07/01 14:18:58 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(void *t)
{
	t_arg	*a;

	a = (t_arg *)t;
	free(a->str);
	free(a);
}

void	free_all(t_data *shell)
{
	int	n;

	clear_history();
	n = -1;
	while (shell->env[++n])
		free(shell->env[n]);
	free(shell->env);
	n = -1;
	if (shell->env_path)
	{
		while (shell->env_path[++n])
			free(shell->env_path[n]);
		free(shell->env_path);
	}
	free(shell);
}

void	free_cmd(t_lst *cmd)
{
	t_lst	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		if (tmp->argv != NULL)
		{
			while (tmp->argv[i])
			{
				free(tmp->argv[i]->str);
				if (tmp->argv[i]->d_quotes)
					ft_lstclear(&(tmp->argv[i]->d_quotes), &free);
				if (tmp->argv[i]->s_quotes)
					ft_lstclear(&(tmp->argv[i]->s_quotes), &free);
				free(tmp->argv[i]);
				i++;
			}
		}
		if (tmp->p_cmd)
			free(tmp->p_cmd);
		cmd = cmd->next;
		free(tmp);
		tmp = cmd;
	}
}
