/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:28:32 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/16 18:16:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nrange(int **range, int min, int max)
{
	int	size;
	int	i;
	int	counter;
	int	*output;

	size = max - min;
	if (min >= max)
	{
		range = NULL;
		return (0);
	}
	output = ft_malloc(sizeof(int) * size);
	i = 0;
	counter = min;
	while (i < size)
	{
		output[i] = counter;
		counter++;
		i++;
	}
	*range = output;
	return (size);
}
