/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:12:36 by estarck           #+#    #+#             */
/*   Updated: 2022/02/24 14:22:29 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0 && (*(unsigned char *)s != (unsigned char)c))
	{
		s++;
		n--;
	}
	if (n == 0)
		return (0x0);
	else
		return ((void *)s);
}
