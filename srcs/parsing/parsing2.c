/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:44:55 by reclaire          #+#    #+#             */
/*   Updated: 2022/07/01 02:44:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push2(t_pars_dat *d, t_arg *arg)
{
	d->new = NULL;
	d->lst_s_quotes = NULL;
	d->lst_d_quotes = NULL;
	ft_lstadd_back(&d->args, ft_lstnew(arg));
}

void	push(t_pars_dat *d, t_type type)
{
	char	*new2;
	int		i;
	t_arg	*arg;

	if (d->new == NULL)
		return ;
	arg = ft_malloc(sizeof(t_arg));
	arg->str = d->new;
	arg->type = type;
	arg->d_quotes = d->lst_d_quotes;
	arg->s_quotes = d->lst_s_quotes;
	new2 = ft_strdup("");
	i = 0;
	while (d->new[i])
	{
		if (!(d->new[i] == 32 || (d->new[i] >= 9 && d->new[i] <= 13))
			|| is_in_quotes(i, arg))
			append_char(d, &new2, d->new[i], 0);
		i++;
	}
	arg->str = new2;
	free(d->new);
	push2(d, arg);
}

void	cpy_cmd(t_data *shell)
{
	int		i;
	t_list	*tmp;
	t_lst	*cmd;

	i = 0;
	tmp = shell->cmd_list;
	cmd = shell->cmd;
	while (tmp)
	{
		while (tmp && ((t_arg *)tmp->content)->type != PIPE)
		{
			cmd->argv[i] = tmp->content;
			check_redir(shell, cmd, i);
			i++;
			tmp = tmp->next;
		}
		cmd->argv[i] = NULL;
		i = 0;
		if (tmp)
		{
			cmd = cmd->next;
			tmp = tmp->next;
		}
	}
}

void	init_cmd(t_data *shell)
{
	int		i;
	t_list	*tmp;
	t_lst	*cmd;

	i = 1;
	tmp = shell->cmd_list;
	shell->cmd = new_cmd();
	cmd = shell->cmd;
	while (tmp)
	{
		if (((t_arg *)tmp->content)->type == PIPE || tmp->next == NULL)
		{
			if (((t_arg *)tmp->content)->type == PIPE)
				i--;
			cmd->argv = malloc(sizeof(t_arg *) * (i + 1));
			i = 1;
			tmp = tmp->next;
			if (tmp)
				cmd = add_cmd(shell->cmd);
			continue ;
		}
		i++;
		tmp = tmp->next;
	}
}

void	append_char(t_pars_dat *d, char **str, char c, int t)
{
	char	*cpy;

	cpy = ft_malloc(sizeof(char) * 2);
	cpy[0] = c;
	cpy[1] = '\0';
	*str = ft_str_appnd(*str, cpy, 1, 1);
	if (t)
		d->escape = 0;
}
