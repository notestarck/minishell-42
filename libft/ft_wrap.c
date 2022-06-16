/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:03 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/08 15:54:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wrap(int min, int max, int n)
{
	int	range;

	range = max - min + 1;
	n = ((n - min) % range);
	if (n < 0)
		return (max + 1 + n);
	else
		return (min + n);
}
