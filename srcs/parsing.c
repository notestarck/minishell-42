/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:52:00 by estarck           #+#    #+#             */
/*   Updated: 2022/06/29 19:33:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_arg(t_lst *cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '|' && str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|' || str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == '\'' || str[i] == '"')
				i = check_quote(cmd, &str[i]) + i + 1;
			else if ((str[i] == '>' || str[i] == '<') && str[i + 1] != '>' && str[i + 1] != '<' && str[i - 1] != '\\' && str[i])
				i++;
			else if ((str[i] == '>' || str[i] == '<') && (str[i + 1] == '>' || str[i + 1] == '<') && str[i - 1] != '\\' && str[i])
				i += 2;
			break ;
		}
		else if (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i])
		{
			while (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != 32 && !(str[i] >= 9 && str[i] <= 13) && str[i])
			{
				if (str[i] == '\'' || str[i] == '"')
					i = check_quote(cmd, &str[i]) + i + 1;
				if (str[i] == '\\')
					i += 2;
				else
					i++;
			}
			break ;
		}
	printf("i = %d\n", i);
	}
	return (i);
}

static int	cpy_arg(t_lst *cmd, char *str)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	while (str[i] && (str[i] != '|' || str[i + 1] == '|'))
	{
		l = 0;
		l = parse_arg(cmd, &str[i]);
		cmd->argv[j] = malloc(sizeof(char) * (l + 1));
		if (!cmd->argv[j])
			perror("error : malloc");
		ft_strlcpy(cmd->argv[j], &str[i], l + 1);
		i = i + l;
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		j++;
	}
	cmd->argv[j] = NULL;
	if (str[i] == '|')
		i++;
	return (i);
}

static void	init_arg(t_lst *cmd, char *str)
{
	cmd->argv = malloc(sizeof(char *) * (count_argv(cmd, str) + 1));
	if (!cmd->argv)
		perror("error : malloc");
}

static void	split(t_data *shell, t_lst *cmd)
{
	t_lst	*tmp;
	char	*str;

	tmp = cmd;
	str = ft_strcut(shell->ret_prompt, ' ');
	if (*str == '\0')
		cmd->error = 1;
	while (*str != '\0')
	{
		init_arg(tmp, str);
		str = cpy_arg(tmp, str) + str;
		if (*str != '\0')
		{
			shell->nbr_cmd = shell->nbr_cmd + 1;
			tmp = add_cmd(cmd);
			str = ft_strcut(str, ' ');
		}
	}
}

void	append_char(char **str, char c)
{
	char	*cpy;

	cpy = ft_malloc(sizeof(char) * 2);
	cpy[0] = c;
	cpy[1] = '\0';
	*str = ft_str_appnd(*str, cpy, 1, 1);
}

int	pre_process(t_data *shell)
{
	int		i;
	int		escape;
	int		s_quote;
	int		d_quote;
	int		d_quote_escape;
	int		size;
	char	*str;
	char	*new;

	i = 0;
	size = 0;
	escape = 0;
	d_quote_escape = 0;
	s_quote = 0;
	d_quote = 0;
	str = shell->ret_prompt;
	new = ft_malloc(sizeof(char));
	*new = '\0';
	while (str[i])
	{
		if (s_quote)
		{
			if (str[i] == '\'')
			{
				s_quote = 0;
				i++;
				continue ;
			}
			append_char(&new, str[i]);
			i++;
			continue ;
		}
		if (d_quote)
		{
			if (str[i] == '\"' && !d_quote_escape)
			{
				d_quote = 0;
				i++;
				continue ;
			}
			else if (str[i] == '\\' && d_quote_escape)
			{
				d_quote_escape = 0;
				append_char(&new, str[i]);
				i++;
				continue ;
			}
			else if (str[i] == '\\' && !d_quote_escape)
			{
				d_quote_escape = 1;
				i++;
				continue ;
			}
			d_quote_escape = 0;
			append_char(&new, str[i]);
			i++;
			continue ;
		}
		if (str[i] == '\'' && !escape)
		{
			s_quote = 1;
			i++;
			continue ;
		}
		if (str[i] == '\"' && !escape)
		{
			d_quote = 1;
			i++;
			continue ;
		}
		if (str[i] == '\\' && !escape)
		{
			escape = 1;
			i++;
			continue ;
		}
		if (ft_strchr("><|", str[i]) && escape)
		{
			escape = 0;
			append_char(&new, str[i]);
			i++;
			continue ;
		}
		if (!ft_strncmp(str + i, ">>", 2))
		{
			append_char(&new, ' ');
			append_char(&new, '>');
			append_char(&new, '>');
			append_char(&new, ' ');
			i += 2;
			continue ;
		}
		if (!ft_strncmp(str + i, "<<", 2))
		{	
			append_char(&new, ' ');
			append_char(&new, '<');
			append_char(&new, '<');
			append_char(&new, ' ');
			i += 2;
			continue ;
		}
		if (!ft_strncmp(str + i, ">", 1))
		{	
			append_char(&new, ' ');
			append_char(&new, '>');
			append_char(&new, ' ');
			i++;
			continue ;
		}
		if (!ft_strncmp(str + i, "<", 1))
		{	
			append_char(&new, ' ');
			append_char(&new, '<');
			append_char(&new, ' ');
			i++;
			continue ;
		}
		escape = 0;
		append_char(&new, str[i]);
		i++;
	}
	free(shell->ret_prompt);
	shell->ret_prompt = new;
	if (s_quote || d_quote)
		return (0);
	return (1);
}

t_lst	*parse_prompt(t_data *shell)
{
	t_lst	*cmd;

	cmd = new_cmd();
	shell->nbr_cmd = 1;
	if (!pre_process(shell))
		cmd->error = 1;
	cmd->error = 1;
	ft_printf("STR=%s\n", shell->ret_prompt);
	split(shell, cmd);
	return (cmd);
}
