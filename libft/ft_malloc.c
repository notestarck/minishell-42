/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:31:07 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/31 00:31:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*out;

	out = malloc(size);
	if (!out)
	{
		ft_printf("error: malloc\n");
		exit(1);
	}
	return (out);
}
