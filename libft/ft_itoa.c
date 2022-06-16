/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:49:50 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/03 15:50:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_digits(long n)
{
	int	r;

	r = 0;
	if (n < 0)
	{
		n *= -1;
		r++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		r++;
	}
	return (r);
}

void	check_negative(long *nb, char *str)
{
	if (*nb < 0)
	{
		*nb *= -1;
		str[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	long	nb;
	int		i;
	char	*str;

	nb = n;
	i = num_digits(nb);
	str = ft_malloc((i + 1) * sizeof(char));
	str[i--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	check_negative(&nb, str);
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (str);
}
