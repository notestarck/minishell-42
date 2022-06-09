/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:32:06 by estarck           #+#    #+#             */
/*   Updated: 2022/03/15 19:02:51 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_checkformat(va_list arg_ptr, const char *format)
{
	if (*format == 'c')
		return (ft_putchar_pf(va_arg(arg_ptr, int), 1));
	if (*format == 's')
		return (ft_putstr_pf(va_arg(arg_ptr, char *), 1));
	if (*format == 'p')
		return (ft_ptrhexa(va_arg(arg_ptr, unsigned long long)));
	if (*format == 'd' || *format == 'i')
		return (ft_putnbr_pf(va_arg(arg_ptr, int), 1));
	if (*format == 'u')
		return (ft_uputnbr_pf(va_arg(arg_ptr, unsigned int), 1));
	if (*format == 'x' || *format == 'X')
		return (ft_printhexa(va_arg(arg_ptr, unsigned int), format));
	if (*format == '%')
		return (ft_putchar_pf(37, 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	arg_ptr;

	i = 0;
	va_start(arg_ptr, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			i += ft_checkformat(arg_ptr, (format + 1));
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			i++;
		}
		format++;
	}
	va_end(arg_ptr);
	return (i);
}
