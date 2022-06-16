/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:42:29 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/03 15:50:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t				s1_len;
	size_t				s2_len;
	char				*new;
	unsigned long		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = ft_malloc((s1_len + s2_len + 1) * sizeof(char));
	i = 0;
	while (i < s1_len)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < s2_len + s1_len)
	{
		new[i] = s2[i - s1_len];
		i++;
	}
	new[i] = '\0';
	return (new);
}
