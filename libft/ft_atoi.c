/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:51:00 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 22:52:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int						i;
	int						neg;
	unsigned long long int	result;

	result = 0;
	neg = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > 9223372036854775807 && neg < 0)
		return (0);
	if (result >= 9223372036854775807 && neg > 0)
		return (-1);
	return (result * neg);
}
