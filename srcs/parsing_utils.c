/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:04:41 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 20:41:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_in_quotes(int i, t_arg *arg)
{
	t_list	*lst1;
	t_list	*lst2;

	lst1 = arg->s_quotes;
	lst2 = arg->d_quotes;
	while (lst1)
	{
		if (*((int *)lst1->content) <= i && i <= *((int *)lst1->next->content))
			return (1);
		lst1 = lst1->next->next;
	}
	while (lst2)
	{
		if (*((int *)lst2->content) <= i && i <= *((int *)lst2->next->content))
			return (2);
		lst2 = lst2->next->next;
	}
	return (0);
}

t_lst	*add_cmd(t_lst *cmd)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (new == NULL)
		perror("error : malloc");
	while (cmd->next != NULL)
		cmd = cmd->next;
	new->error = 0;
	new->er_quote = 0;
	new->built = -1;
	new->sep = -1;
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
	new->er_quote = 0;
	new->built = -1;
	new->sep = -1;
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
	while (str[i])
	{
		while ((str[i] == '\\' || str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i])
			i++;
		while ((str[i] != 32 && !(str[i] >= 9 && str[i] <= 13)) && str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				c++;
				i = check_quote(cmd, &str[i]) + i + 1;
			}
			else if ((str[i] == '>' || str[i] == '<') && str[i + 1] != '>' && str[i + 1] != '<' && str[i])
			{
				i++;
				c++;
			}
			else if (((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) && str[i])
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
	return (c);
}
