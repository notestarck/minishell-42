/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:30:23 by estarck           #+#    #+#             */
/*   Updated: 2022/06/17 12:38:12 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(t_lst *cmd)
{
	while (cmd)
	{
		if (cmd->error == 1)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

int	check_quote(t_lst *cmd, char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	if (str[i] == '\'')
		s_quote = 1;
	else if (str[i] == '"')
		d_quote = 1;
	while ((s_quote || d_quote) && str[++i] != '\0')
	{
		if (str[i] == '\'' && s_quote == 1)
			s_quote = 0;
		if (str[i] == '"' && d_quote == 1)
			d_quote = 0;
		if (str[i] == '\\')
			i++;
	}
	if (s_quote || d_quote)
		cmd->error = 1;
	return (i);
}

void	del_quote(t_data *shell)
{
	int		i;
	char	*str;
	t_lst	*tmp;

	tmp = shell->cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->argv[i])
		{
			if ((tmp->argv[i][0] == '\'' || tmp->argv[i][0] == '"')
				&& (ft_strncmp(tmp->argv[0], "echo", 4)
				&& ft_strncmp(tmp->argv[0], "ECHO", 4)))
			{
				if (tmp->argv[i][0] == '\'')
					str = *ft_split(tmp->argv[i], '\'');
				else
					str = *ft_split(tmp->argv[i], '"');
				free(tmp->argv[i]);
				tmp->argv[i] = str;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
