/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:16:20 by estarck           #+#    #+#             */
/*   Updated: 2022/03/09 09:53:54 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (src[c] != '\0')
		c++;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src [i];
			i++;
		}
		dst[i] = '\0';
	}
	return (c);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lsrc;

	i = 0;
	j = 0;
	lsrc = 0;
	while (src[lsrc] != '\0')
		lsrc++;
	while (dst[i] && i < dstsize)
		i++;
	if (!dstsize)
		return (dstsize + lsrc);
	while (src[j] && (i + j < dstsize - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + lsrc);
}

size_t	ft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
	{
		l++;
	}
	return (l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;

	r = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (r == 0x0)
		return (0x0);
	ft_strlcpy(r, s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(r, s2, ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	return (r);
}
