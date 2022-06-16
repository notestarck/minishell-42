/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:22:43 by estarck           #+#    #+#             */
/*   Updated: 2022/05/17 23:33:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lsrc;

	i = 0;
	j = 0;
	lsrc = 0;
	while (src[lsrc] != '\0')
		lsrc++;
	while (dest[i] && i < size)
		i++;
	if (!size)
		return (size + lsrc);
	while (src[j] && (i + j < size - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = '\0';
	return (i + lsrc);
}
