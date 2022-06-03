/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:35:14 by estarck           #+#    #+#             */
/*   Updated: 2022/03/25 17:24:41 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_raw_int(char c)
{
	if (ft_isalpha(c))
	{
		return (ft_toupper(c) - 'A' + 10);
	}
	return (c - '0');
}

long	ft_htol(char *hex)
{
	int		i;
	int		power;
	long	dec;

	i = ft_strlen(hex) - 1;
	power = 1;
	dec = 0;
	while (i >= 0)
	{
		dec += ft_get_raw_int(hex[i]) * power;
		power *= 16;
		i--;
	}
	return (dec);
}
