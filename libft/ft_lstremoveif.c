/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 02:05:10 by reclaire          #+#    #+#             */
/*   Updated: 2022/06/02 02:05:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstremoveif(t_list **lst, void (*del)(void *), int (*f)(), void *ref)
{
	t_list	*prev;
	t_list	*curr;

	if (!f || !lst || !(*lst))
		return (-1);
	curr = (*lst);
	prev = NULL;
	while (curr)
	{
		if (f(curr->content, ref))
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
