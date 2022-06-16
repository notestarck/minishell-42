/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:43:53 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/29 15:18:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

int	parse(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == '%')
		i += write(1, "%", 1);
	else if (c == 'c')
		i += handle_c(va_arg(args, unsigned int));
	else if (c == 'd')
		i += handle_d(va_arg(args, int));
	else if (c == 'i')
		i += handle_i(va_arg(args, int));
	else if (c == 'p')
		i += handle_p(va_arg(args, uintptr_t));
	else if (c == 's')
		i += handle_s(va_arg(args, char *));
	else if (c == 'u')
		i += handle_u(va_arg(args, unsigned int));
	else if (c == 'X')
		i += handle_ux(va_arg(args, int));
	else if (c == 'x')
		i += handle_x(va_arg(args, unsigned int));
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	va_list		args;
	int			c_count;

	va_start(args, str);
	i = 0;
	c_count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			c_count += parse(str[i + 1], args);
			i++;
		}
		else
		{
			c_count++;
			ft_putchar_fd(str[i], 1);
		}
		i++;
	}
	va_end(args);
	return (c_count);
}
