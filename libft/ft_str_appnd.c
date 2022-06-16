/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_appnd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:24:52 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/31 00:24:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_appnd(char *a, char *b, int free_a, int free_b)
{
	char	*new;

	new = ft_strjoin(a, b);
	if (free_a)
		free(a);
	if (free_b)
		free(b);
	return (new);
}
