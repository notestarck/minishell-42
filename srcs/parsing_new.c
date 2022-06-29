/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:21:38 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/28 21:44:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c && ((c >= 9 && c <= 13) || c == 32))
		return (1);
	else
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

int	is_in_quotes(char *str)
{
	int	i;
	int	is_in_simple;
	int	is_in_double;

	i = 0;
	is_in_simple = 0;
	is_in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_in_simple && !is_in_double)
			is_in_simple = 1;
		else if (str[i] == '\'' && is_in_simple)
			is_in_simple = 0;
		if (str[i] == '\"' && !is_in_double && !is_in_simple)
			is_in_double = 1;
		else if (str[i] == '\"' && is_in_double)
			is_in_double = 0;
	}
}

void	parse(char *str, t_data *shell)
{
	int	i;
	int	n;
	int	is_quote;

	check_quote(str);
	i = 0;
	while (is_whitespace(str[i]))
		i++;
	n = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' && is_quote)
		if (is_whitespace(str[i]))
		{
			n++;
			while (is_whitespace(str[i]))
				i++;
		}
		else if (!ft_strncmp(str + i, ">>", 2)
				|| !ft_strncmp(str + i, "<<", 2))
		{
			i += 2;
			n++;
		}
		else if (!ft_strncmp(str + i, ">", 1)
				|| !ft_strncmp(str + i, "<", 1))
		{
			i++;
			n++;
		}
		else if (str[i] == '|')
		{
			
		}
		i++;
	}



}


t_lst	*parse_prompt(t_data *shell)
{
	t_lst	*cmd;

	if (shell->ret_prompt == '\0')
		return (NULL);
	cmd = new_cmd();

	return (cmd);
}