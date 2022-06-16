/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:11:58 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/16 18:15:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int	size;
	int	i;
	int	counter;
	int	*output;

	i = 0;
	size = max - min;
	if (size <= 0)
		return (NULL);
	output = ft_malloc(sizeof(int) * size + 1);
	counter = min;
	while (i < size)
	{
		output[i] = counter;
		counter++;
		i++;
	}
	return (output);
}
