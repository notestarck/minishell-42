/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/29 15:11:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

static void	convert(uintptr_t num, int *i)
{
	char	*hexa;

	hexa = "0123456789abcdef";
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

int	handle_p(uintptr_t p)
{
	int	i;

	i = 0;
	ft_putstr_fd("0x", 1);
	convert(p, &i);
	return (i + 2);
}
