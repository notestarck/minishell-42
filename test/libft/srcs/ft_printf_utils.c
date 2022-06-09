/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:32:06 by estarck           #+#    #+#             */
/*   Updated: 2022/03/15 18:41:51 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_pf(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

int	ft_putstr_pf(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (s[i] != '\0')
	{
		write (fd, (s + i), 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_pf(int n, int fd)
{
	char		*str;
	int			i;

	i = 0;
	str = ft_itoa(n);
	i = ft_putstr_pf(str, fd);
	free(str);
	return (i);
}

int	ft_uputnbr_pf(unsigned int n, int fd)
{
	char		*str;
	int			i;

	i = 0;
	str = ft_uitoa(n);
	i = ft_putstr_pf(str, fd);
	free(str);
	return (i);
}
