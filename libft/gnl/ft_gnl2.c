/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:09:38 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 23:05:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"
#include "libft.h"

t_list	*gnl_addback(t_list **lst, int fd)
{
	t_list	*current_last;
	t_list	*new;
	t_list	*previous;

	new = ft_malloc(sizeof(t_list));
	new->content = gnl_lstnew(fd);
	new->next = NULL;
	current_last = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current_last != NULL)
		{
			previous = current_last;
			current_last = current_last->next;
		}
		previous->next = new;
	}
	return (new);
}

t_save	*gnl_lstnew(int fd)
{
	t_save	*new;

	new = ft_malloc(sizeof(t_save));
	new->fd = fd;
	new->save = ft_malloc(sizeof(char));
	(new->save)[0] = '\0';
	return (new);
}

void	gnl_lstfree(t_list **first, int fd)
{
	t_list	*current;
	t_list	*previous;

	current = *first;
	previous = NULL;
	while (current)
	{
		if (((t_save *)(current->content))->fd == fd)
			break ;
		previous = current;
		current = current->next;
	}
	if (!previous)
	{
		if (current->next)
			*first = current->next;
		else
			*first = NULL;
	}
	else
		previous->next = current->next;
	free(((t_save *)(current->content))->save);
	free(current->content);
	free(current);
}
