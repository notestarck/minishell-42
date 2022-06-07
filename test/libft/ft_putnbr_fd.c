/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:44:54 by estarck           #+#    #+#             */
/*   Updated: 2022/03/01 10:04:21 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	r;

	r = n;
	if (r < 0)
	{
		r = -r;
		write(fd, "-", 1);
	}
	if (r > 9)
	{
		ft_putnbr_fd(r / 10, fd);
		ft_putchar_fd((r % 10) + '0', fd);
	}
	else
		ft_putchar_fd(r + '0', fd);
}
