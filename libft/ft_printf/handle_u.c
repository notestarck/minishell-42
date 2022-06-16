/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:28:55 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/17 14:22:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	handle_u(unsigned int i)
{
	char			*out;
	int				l;

	i = (unsigned int)(4294967295 + 1
			+ i);
	out = ft_uitoa(i);
	l = ft_strlen(out);
	ft_putstr_fd(out, 1);
	free(out);
	return (l);
}
