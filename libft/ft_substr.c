/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:39:44 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/03 15:50:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;

	if (ft_strlen((char *)s) <= start)
	{
		r = (char *)ft_malloc(sizeof(char) * 1);
		r[0] = '\0';
		return (r);
	}
	r = (char *)ft_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(r, (char *)(s + start), len + 1);
	return (r);
}
