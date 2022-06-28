/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:04:41 by estarck           #+#    #+#             */
/*   Updated: 2022/06/23 16:39:56 by estarck          ###   ########.fr       */
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

int	count_argv(t_data *shell, t_lst *cmd, char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] && (str[i] != '|' || str[i + 1] == '|'))
	{
		if (str[i] != ' ')
		{
			c++;
			while (str[i] != ' ' && str[i])
			{
				if (str[i] == '\'' || str[i] == '"')
					i = check_quote(cmd, &str[i]) + i;
				i++;
			}
		}
		while (str[i] == ' ' && str[i])
			i++;
	}
	return (c);
}
