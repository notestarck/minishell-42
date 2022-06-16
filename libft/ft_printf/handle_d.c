/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/29 14:43:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_d(int i)
{
	char	*out;
	int		l;

	if (i == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	out = ft_itoa(i);
	l = ft_strlen(out);
	ft_putstr_fd(out, 1);
	free(out);
	return (l);
}
