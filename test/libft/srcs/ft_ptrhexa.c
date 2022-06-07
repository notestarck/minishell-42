/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrhexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 22:22:47 by estarck           #+#    #+#             */
/*   Updated: 2022/03/15 18:41:35 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_counthexa(unsigned long long ptr)
{
	int	i;

	i = 0;
	while (ptr >= 16)
	{
		ptr = ptr / 16;
		i++;
	}
	i++;
	return (i);
}

static void	ft_puthexa(unsigned long long ptr)
{
	if (ptr >= 16)
	{
		ft_puthexa(ptr / 16);
		ft_puthexa(ptr % 16);
	}
	else
	{
		if (ptr < 10)
			ft_putchar_fd(ptr + '0', 1);
		else
			ft_putchar_fd(ptr - 10 + 'a', 1);
	}
}

int	ft_ptrhexa(unsigned long long ptr)
{
	write(1, "0x", 2);
	ft_puthexa(ptr);
	return (ft_counthexa(ptr) + 2);
}
