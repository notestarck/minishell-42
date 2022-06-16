/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:51:38 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/03 15:50:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		l;
	char	*dup;

	l = 0;
	while (s1[l] != '\0')
		l++;
	dup = ft_malloc((l + 1) * sizeof(char));
	dup[l] = '\0';
	l = 0;
	while (s1[l] != '\0')
	{
		dup[l] = s1[l];
		l++;
	}
	return (dup);
}
