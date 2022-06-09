/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:29:42 by estarck           #+#    #+#             */
/*   Updated: 2022/03/22 17:47:27 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_counthexa(unsigned int n)
{
	int	i;

	i = 0;
	while (n >= 16)
	{
		n = n / 16;
		i++;
	}
	i++;
	return (i);
}

static void	ft_puthexa(unsigned int n, const char *format)
{
	if (n >= 16)
	{
		ft_puthexa(n / 16, format);
		ft_puthexa(n % 16, format);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', 1);
		else
		{
			if (*format == 'x')
				ft_putchar_fd(n - 10 + 'a', 1);
			if (*format == 'X')
				ft_putchar_fd(n - 10 + 'A', 1);
		}
	}
}

int	ft_printhexa(unsigned int n, const char *format)
{
	if (n == 0)
		write(1, "0", 1);
	else
		ft_puthexa(n, format);
	return (ft_counthexa(n));
}
