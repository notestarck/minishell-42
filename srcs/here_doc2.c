/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:30:51 by estarck           #+#    #+#             */
/*   Updated: 2022/09/07 18:47:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_cat(t_lst *cmd)
{
	t_arg	**argv;

	argv = malloc(sizeof(t_arg *) * 2);
	argv[0] = ft_malloc(sizeof(t_arg));
	argv[0]->d_quotes = NULL;
	argv[0]->s_quotes = NULL;
	argv[0]->type = ARG;
	argv[0]->str = ft_strdup("cat");
	argv[1] = NULL;
	cmd->argv = argv;
}

void	repars_heredocs2(t_lst *cmd, t_arg **argv)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		if (!ft_strncmp(cmd->argv[i]->str, "<<", 2))
		{
			free_arg(cmd->argv[i]);
			free_arg(cmd->argv[i + 1]);
			i += 2;
			continue ;
		}
		argv[j] = cmd->argv[i];
		j++;
		i++;
	}
	argv[j] = NULL;
	free(cmd->argv);
	cmd->argv = argv;
}

void	repars_heredocs(t_lst *cmd)
{
	t_arg	**argv;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		if (!ft_strncmp(cmd->argv[i]->str, "<<", 2))
		{
			i += 2;
			continue ;
		}
		j++;
		i++;
	}
	if (j == 0)
	{
		write_cat(cmd);
		return ;
	}
	argv = ft_malloc(sizeof(t_arg *) * (j + 1));
	repars_heredocs2(cmd, argv);
}
