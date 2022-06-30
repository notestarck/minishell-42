/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:59:18 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 23:35:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_dchar(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
				ft_lstclear(&(tmp->argv[i]->d_quotes), &free);
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
