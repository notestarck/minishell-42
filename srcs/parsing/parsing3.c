/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 04:34:27 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/07 17:21:05 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars_dat	*create_dat(t_data *shell)
{
	t_pars_dat	*d;

	d = ft_malloc(sizeof(t_pars_dat));
	d->i = 0;
	d->escape = 0;
	d->d_quote_escape = 0;
	d->s_quote = 0;
	d->d_quote = 0;
	d->str = shell->ret_prompt;
	d->new = ft_strdup("");
	d->lst_d_quotes = NULL;
	d->lst_s_quotes = NULL;
	d->args = NULL;
	return (d);
}

void	add_quote(t_pars_dat *d, int t, int v, int j)
{
	int	*n;
	int	k;

	k = 0;
	while (k < j)
	{
		n = ft_malloc(sizeof(int));
		*n = v;
		if (t == 1)
		{
			d->s_quote = !d->s_quote;
			ft_lstadd_back(&d->lst_s_quotes, ft_lstnew(n));
		}
		else if (t == 2)
		{
			d->d_quote = !d->d_quote;
			ft_lstadd_back(&d->lst_d_quotes, ft_lstnew(n));
		}
		k++;
	}
}

int	handle_s_quotes(t_pars_dat *d)
{
	if (d->s_quote)
	{
		if (d->str[d->i] == '\'')
			add_quote(d, 1, ft_strlen(d->new) - 1, 1);
		else
			append_char(d, &d->new, d->str[d->i], 0);
		d->i++;
		return (1);
	}
	return (0);
}

int	handle_d_quotes(t_pars_dat *d)
{
	if (d->d_quote)
	{
		if (d->str[d->i] == '\"' && !d->d_quote_escape)
			add_quote(d, 2, ft_strlen(d->new) - 1, 1);
		else if (d->str[d->i] == '\\' && d->d_quote_escape)
		{
			d->d_quote_escape = 0;
			append_char(d, &d->new, d->str[d->i], 0);
		}
		else if (d->str[d->i] == '\\' && !d->d_quote_escape)
			d->d_quote_escape = 1;
		else
		{
			if (d->d_quote_escape)
				add_quote(d, 1, ft_strlen(d->new), 2);
			d->d_quote_escape = 0;
			append_char(d, &d->new, d->str[d->i], 0);
		}
		d->i++;
		return (1);
	}
	return (0);
}
