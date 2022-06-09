/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:28:47 by estarck           #+#    #+#             */
/*   Updated: 2022/02/25 15:22:38 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*a;

	a = 0x0;
	while (*s != '\0')
	{
		if (*s == (const char)c)
			a = (char *)s;
		s++;
	}
	if (*s == (const char)c)
		a = (char *)s;
	return (a);
}
