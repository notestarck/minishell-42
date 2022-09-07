/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:40:55 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/07 16:26:20 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_specials2(t_pars_dat *d)
{
	if (d->str[d->i] == '|' && !d->escape)
	{
		push(d, ARG);
		d->new = ft_strdup("|");
		push(d, PIPE);
		d->new = ft_strdup("");
		d->i++;
		return (1);
	}
	return (0);
}

int	handle_specials(t_pars_dat *d)
{
	if (d->str[d->i] == '\'' && !d->escape)
	{
		add_quote(d, 1, ft_strlen(d->new), 1);
		d->i++;
		return (1);
	}
	else if (d->str[d->i] == '\"' && !d->escape)
	{
		add_quote(d, 2, ft_strlen(d->new), 1);
		d->i++;
		return (1);
	}
	else if (d->str[d->i] == '\\' && !d->escape)
	{
		d->escape = 1;
		d->i++;
		return (1);
	}
	else
		return (handle_specials2(d));
}

void	pre_process2(t_pars_dat *d)
{
	if (handle_redir(d, '>', 2, D_RIGHT))
		return ;
	else if (handle_redir(d, '<', 2, D_LEFT))
		return ;
	else if (handle_redir(d, '>', 1, S_RIGHT))
		return ;
	else if (handle_redir(d, '<', 1, S_LEFT))
		return ;
	else if ((d->str[d->i] == 32 || (d->str[d->i] >= 9
				&& d->str[d->i] <= 13)) && !d->escape)
	{
		push(d, ARG);
		d->new = ft_strdup("");
	}
	else
	{
		if (d->escape)
			add_quote(d, 1, ft_strlen(d->new), 2);
		append_char(d, &d->new, d->str[d->i], 1);
	}
	d->i++;
}

int	pre_process(t_data *shell)
{
	t_pars_dat	*d;

	d = create_dat(shell);
	d->err = 0;
	while (d->str[d->i])
	{
		if (handle_s_quotes(d))
			continue ;
		if (handle_d_quotes(d))
			continue ;
		if (handle_specials(d))
			continue ;
		if (ft_strchr("><|", d->str[d->i]) && d->escape)
			append_char(d, &d->new, d->str[d->i], 1);
		else
		{
			pre_process2(d);
			if (d->err == 1)
				return (ft_printf("-minishell: Syntax error\n"), 0);
		}
	}
	push(d, ARG);
	ft_lstremoveif(&d->args, &free_arg, &cmp, NULL);
	shell->cmd_list = d->args;
	if (d->s_quote || d->d_quote)
		return (ft_printf("-minishell: Syntax error\n"), free(d), 0);
	return (free(d), 1);
}

void	parse_prompt(t_data *shell)
{
	t_list	*tmp;

	if (!pre_process(shell))
		shell->code_error = -42;
	init_cmd(shell);
	cpy_cmd(shell);
	while (shell->cmd_list)
	{
		tmp = shell->cmd_list->next;
		free(shell->cmd_list);
		shell->cmd_list = tmp;
	}
}
