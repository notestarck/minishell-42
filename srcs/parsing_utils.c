/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:04:41 by estarck           #+#    #+#             */
/*   Updated: 2022/06/29 14:09:03 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lst	*add_cmd(t_lst *cmd)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (new == NULL)
		perror("error : malloc");
	while (cmd->next != NULL)
		cmd = cmd->next;
	new->error = 0;
	new->built = -1;
	new->sep = -1;
	new->tmpfile = "okkkkkk";
	new->heredoc = 0;
	new->next = NULL;
	new->argv = NULL;
	new->p_cmd = NULL;
	new->prev = cmd;
	cmd->next = new;
	return (new);
}

t_lst	*new_cmd(void)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (new == NULL)
		perror("error : malloc");
	new->error = 0;
	new->built = -1;
	new->sep = -1;
	new->tmpfile = "okkkkkk";
	new->heredoc = 0;
	new->next = NULL;
	new->prev = NULL;
	new->argv = NULL;
	new->p_cmd = NULL;
	return (new);
}

char	*ft_strcut(char *str, char tok)
{
	int	i;

	i = 0;
	while (str[i] == tok && str[i])
		i++;
	return (&str[i]);
}

int	count_argv(t_lst *cmd, char *str)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (str[i] != '|' && str[i])
	{
		while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i])
			i++;
		while ((str[i] != 32 && !(str[i] >= 9 && str[i] <= 13)) && str[i] != '|' && str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				c++;
				i = check_quote(cmd, &str[i]) + i + 1;
			}
			else if ((str[i] == '>' || str[i] == '<') && str[i + 1] != '>' && str[i + 1] != '<' && str[i - 1] != '\\' && str[i])
			{
				i++;
				c++;
			}
			else if ((str[i] == '>' || str[i] == '<') && (str[i + 1] == '>' || str[i + 1] == '<') && str[i - 1] != '\\' && str[i])
			{
				i += 2;
				c++;
			}
			else if (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i])
			{
				c++;
				while (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != 32 && !(str[i] >= 9 && str[i] <= 13) && str[i])
				{
					if (str[i] == '\'' || str[i] == '"')
						i = check_quote(cmd, &str[i]) + i;
					if (str[i] == '\\')
						i += 2;
					else
						i++;
				}
			}
			else if (str[i] == '\\')
			{
				c++;
				i += 2;
			}
		}
	}
	if (str[i] == '|')
		i++;
	return (c);
}
