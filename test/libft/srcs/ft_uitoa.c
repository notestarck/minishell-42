/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:05:31 by estarck           #+#    #+#             */
/*   Updated: 2022/03/14 10:15:04 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(long n)
{
	int	l;

	l = 0;
	if (n < 0)
	{
		n = -n;
		l++;
	}
	while (n > 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static char	*ft_writedest(char *dest, long nb, int i)
{
	if (nb == 0)
		dest[0] = '0';
	if (nb < 0)
	{
		dest[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		dest[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (dest);
}

char	*ft_uitoa(unsigned int n)
{
	char	*dest;
	int		i;
	long	nb;

	nb = n;
	i = ft_len(nb);
	if (nb == 0)
		i = 1;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (dest == 0x0)
		return (0x0);
	dest[i--] = '\0';
	ft_writedest(dest, nb, i);
	return (dest);
}
