/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:29:32 by estarck           #+#    #+#             */
/*   Updated: 2022/02/25 13:25:25 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*tofind == '\0' || tofind == 0x0)
		return ((char *)s);
	while (s[i] != '\0')
	{
		j = 0;
		while (tofind[j] == s[i + j] && i + j < len)
		{
			if (tofind[j + 1] == '\0')
			{
				return ((char *)s + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}
