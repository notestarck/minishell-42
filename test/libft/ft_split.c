/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:37:27 by estarck           #+#    #+#             */
/*   Updated: 2022/03/02 16:49:58 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c);
static int	ft_len(char const *s, char c);
static int	ft_issep(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		l;
	int		i;

	i = 0;
	dest = malloc(sizeof(*dest) * (ft_countwords(s, c) + 1));
	if (dest == 0x0)
		return (0x0);
	while (*s != '\0')
	{
		while (ft_issep(s, c))
			s++;
		if (*s == '\0')
			break ;
		l = (ft_len(s, c));
		dest[i] = malloc(sizeof(char) * (l + 1));
		if (dest[i] == 0x0)
			return (0x0);
		ft_strlcpy(dest[i], s, l + 1);
		s = s + l;
		i++;
	}
	dest[i] = 0x0;
	return (dest);
}

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	cw;

	i = 0;
	cw = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			cw++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == c)
			i++;
	}
	return (cw);
}

static int	ft_len(char const *s, char c)
{
	int	l;

	l = 0;
	while (*s != '\0' && *s != c)
	{
		l++;
		s++;
	}
	return (l);
}

static int	ft_issep(char const *s, char c)
{
	if (*s == c)
		return (1);
	else
		return (0);
}
