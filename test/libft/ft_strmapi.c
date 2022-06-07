/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:22:51 by estarck           #+#    #+#             */
/*   Updated: 2022/02/28 18:16:31 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	i;

	dest = ft_strdup(s);
	if (dest == 0x0)
		return (0x0);
	i = 0;
	while (dest[i])
	{
		dest [i] = f(i, s[i]);
		i++;
	}
	return (dest);
}
