/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:30:23 by estarck           #+#    #+#             */
/*   Updated: 2022/06/28 18:36:53 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(t_lst *cmd)
{
	t_lst	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->error == 1)
			return (1);
		if (*tmp->argv == NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
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

static void	check_sep(t_data *shell)
{
	int		i;
	t_lst	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		i = 0;
		if (!cmd->argv)
		{
			cmd = cmd->next;
			continue ;
		}
		while (cmd->argv[i])
		{
			if (cmd->argv[i][0] == '<' && cmd->argv[i][1] == '\0')
				cmd->sep = S_LEFT;
			else if (cmd->argv[i][0] == '>' && cmd->argv[i][1] == '\0')
				cmd->sep = S_RIGHT;
			else if (cmd->argv[i][0] == '<' && cmd->argv[i][1]
				== '<' && cmd->argv[i][2] == '\0')
				cmd->heredoc = D_LEFT;
			else if (cmd->argv[i][0] == '>' && cmd->argv[i][1]
				== '>' && cmd->argv[i][2] == '\0')
				cmd->sep = D_RIGHT;
			else if (cmd->argv[i][0] == '&' && cmd->argv[i][1]
				== '&' && cmd->argv[i][2] == '\0')
				cmd->sep = AND;
			else if (cmd->argv[i][0] == '|' && cmd->argv[i][1]
				== '|' && cmd->argv[i][2] == '\0')
				cmd->sep = OR;
			else if (cmd->argv[i][0] == '*')
				cmd->sep = WLCRD;
			i++;
		}
		cmd = cmd->next;
	}
}

void	check_syntax(t_data *shell)
{
	check_sep(shell);
}
