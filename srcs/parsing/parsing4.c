/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:20:18 by estarck           #+#    #+#             */
/*   Updated: 2022/09/07 17:27:46 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir2(t_pars_dat *d, char *ref, t_type type, int j)
{
	push(d, ARG);
	d->new = ft_strdup(ref);
	push(d, type);
	d->new = ft_strdup("");
	d->i += ft_strlen(ref);
	free(ref);
	while (d->str[d->i + j])
	{
		if (ft_isalnum(d->str[d->i + j]))
			return (1);
		if (!(d->str[d->i + j] == 32 || (d->str[d->i + j] >= 9
					&& d->str[d->i + j] <= 13)))
			break ;
		j++;
	}
	d->err = 1;
	return (0);
}

int	handle_redir(t_pars_dat *d, char c, int size, t_type type)
{
	char	*ref;
	int		j;

	j = 0;
	ref = ft_malloc(sizeof(char) * (size + 1));
	size--;
	ref[size + 1] = '\0';
	while (size >= 0)
	{
		ref[size] = c;
		size--;
	}
	if (!ft_strncmp(d->str + d->i, ref, ft_strlen(ref)))
	{
		handle_redir2(d, ref, type, j);
		return (1);
	}
	free(ref);
	return (0);
}
