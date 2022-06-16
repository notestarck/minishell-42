/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:15:23 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/18 13:12:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*compute(long nbr, int len)
{
	int		isneg;
	char	*rtn;

	rtn = ft_malloc(sizeof(char) * (len + 1));
	isneg = 0;
	if (nbr < 0)
	{
		isneg++;
		nbr = -nbr;
	}
	rtn[len] = '\0';
	while (--len)
	{
		rtn[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (isneg == 1)
		rtn[0] = '-';
	else
		rtn[0] = (nbr % 10) + '0';
	return (rtn);
}

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*rtn;
	long	nbr;

	nbr = n;
	if (nbr == 0)
		return (ft_strdup("0"));
	len = ft_magnitude(nbr);
	rtn = compute(nbr, len);
	if (!rtn)
		return (0);
	return (rtn);
}
