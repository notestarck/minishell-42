/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:59:57 by estarck           #+#    #+#             */
/*   Updated: 2022/03/02 15:46:15 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*tmp;

	dst = 0x0;
	tmp = 0x0;
	if (lst == 0x0)
		return (0x0);
	while (lst)
	{
		tmp = ft_lstnew(f((*lst).content));
		if (tmp == 0x0)
		{
			ft_lstclear(&tmp, del);
			break ;
		}
		ft_lstadd_back(&dst, tmp);
		lst = (*lst).next;
	}
	ft_lstclear(&lst, del);
	return (dst);
}
