/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:20:56 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 22:38:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test_element(t_list **new_element,
	t_list **lst, t_list **new_lst, void (*del)(void *))
{
	if (!*new_element)
	{
		ft_lstclear(lst, del);
		ft_lstclear(new_lst, del);
		return (0);
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_element;

	if (!f || !del)
		return (NULL);
	new_element = ft_lstnew(f(lst->content));
	if (!test_element(&new_element, &lst, &new_lst, del))
		return (NULL);
	new_lst = new_element;
	lst = lst->next;
	while (lst)
	{
		new_element = ft_lstnew(f(lst->content));
		if (!test_element(&new_element, &lst, &new_lst, del))
			break ;
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_element);
	}
	return (new_lst);
}
