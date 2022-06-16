/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:32:58 by reclaire          #+#    #+#             */
/*   Updated: 2022/03/01 19:51:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			current_last = ft_lstlast(*lst);
			current_last->next = new;
		}
	}
}
