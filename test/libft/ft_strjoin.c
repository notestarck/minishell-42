/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:44:13 by estarck           #+#    #+#             */
/*   Updated: 2022/02/23 21:24:09 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
