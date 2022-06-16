/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:47:40 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/16 11:48:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//unsigned long	count(const char *src)
//{
//	int	i;
//
//	i = 0;
//	while (src[i] != '\0')
//		i++;
//	return (i);
//}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned long	istr;
	int				ifind;
	int				xfind;

	istr = 0;
	ifind = 0;
	if ((to_find[ifind]) == '\0' && ft_strlen(to_find) <= len)
		return ((char *)str);
	while (str[istr] != '\0' && istr < len)
	{
		if (str[istr] == to_find[ifind])
		{
			xfind = istr;
			while (str[istr++] == to_find[ifind++])
			{
				if (to_find[ifind] == '\0' && ft_strlen(to_find) + xfind <= len)
					return ((char *)&str[xfind]);
			}
			istr = xfind;
			ifind = 0;
		}
		istr++;
	}
	return (0x0);
}
