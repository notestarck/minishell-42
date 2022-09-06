/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:04:41 by estarck           #+#    #+#             */
/*   Updated: 2022/09/05 17:17:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmp(t_arg *data, void *ref)
{
	size_t	i;

	(void)ref;
	if (data->str[0] == '\0')
		return (1);
	i = 0;
	while (data->str[i] == 32 || (data->str[i] >= 9 && data->str[i] <= 13))
		i++;
	return (i == ft_strlen(data->str));
}

void	check_redir(t_lst *cmd, int i)
{
	if (ft_isrange((int)(cmd->argv[i]->type), 0, 3))
		cmd->sep = cmd->argv[i]->type;
	if ((int)(cmd->argv[i]->type) == D_LEFT)
		cmd->heredoc = 1;
}

int	is_in_quotes(int i, t_arg *arg)
{
	t_list	*lst1;
	t_list	*lst2;

	lst1 = arg->s_quotes;
	lst2 = arg->d_quotes;
	while (lst1 && lst1->next)
	{
		if (*((int *)lst1->content) <= i && i <= *((int *)lst1->next->content))
			return (1);
		lst1 = lst1->next->next;
	}
	while (lst2 && lst2->next)
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
