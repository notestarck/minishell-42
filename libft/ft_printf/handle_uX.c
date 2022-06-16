/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_uX.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/29 15:12:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	convert(unsigned int num, int *i)
{
	char	*hexa;

	hexa = "0123456789ABCDEF";
	if (num >= 16)
	{
		convert(num / 16, i);
		convert(num % 16, i);
	}
	else
	{
		if (num >= '0' && num <= '9')
			ft_putchar_fd(hexa[num], 1);
		else
			ft_putchar_fd(hexa[num], 1);
		(*i)++;
	}
}

int	handle_ux(unsigned int i)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
		convert(i, &j);
	return (j);
}
