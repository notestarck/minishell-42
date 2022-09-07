/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:59:18 by estarck           #+#    #+#             */
/*   Updated: 2022/09/07 18:42:17 by reclaire         ###   ########.fr       */
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

void	free_targ(t_arg *arg)
{
	free(arg->str);
	if (arg->d_quotes)
		ft_lstclear(&(arg->d_quotes), &free);
	if (arg->s_quotes)
		ft_lstclear(&(arg->s_quotes), &free);
	free(arg);
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
				free_targ(tmp->argv[i++]);
		}
		free(tmp->argv);
		if (tmp->p_cmd)
			free(tmp->p_cmd);
		cmd = cmd->next;
		free(tmp);
		tmp = cmd;
	}
}
