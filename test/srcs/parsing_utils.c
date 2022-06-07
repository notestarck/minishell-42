/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:00:33 by estarck           #+#    #+#             */
/*   Updated: 2022/06/06 10:08:27 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_length(t_shell *shell, char *str)
{
	int	l;

	l = 0;
	while (str[l] != ' ' && str[l])
	{
		if (str[l] == '\'' || str[l] == '"')
			l = check_quote(shell, &str[l]) + l;
		l++;
	}
	return (l);
}

int	count_argv(t_shell *shell, char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] && str[i] != '|')
	{
		if (str[i] != ' ')
		{
			c++;
			while (str[i] != ' ' && str[i])
			{
				if (str[i] == '\'' || str[i] == '"')
					i = check_quote(shell, &str[i]) + i;
				i++;
			}
		}
		while (str[i] == ' ' && str[i])
			i++;
	}
	return (c);
}

t_cmd	*add_lst(t_shell *shell)
{
	t_cmd	*tmp;

	if (shell->cmd == NULL)
	{
		tmp = malloc(sizeof(t_cmd));
		shell->cmd = tmp;
	}
	else
	{
		tmp = shell->cmd;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_cmd));
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		ft_perror("error : malloc", shell, 1);
		exit (0);
	}
	tmp->next = NULL;
	return (tmp);
}
