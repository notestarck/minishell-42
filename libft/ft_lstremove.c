/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:37:06 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/07 16:23:45 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (!lst || !(*lst) || !elem)
		return (-1);
	curr = (*lst);
	prev = NULL;
	while (curr)
	{
		if (elem == curr)
		{
			if (prev == NULL)
				(*lst) = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, del);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
