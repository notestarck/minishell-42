/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:09:34 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 22:46:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H
# define FT_GNL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_save
{
	int				fd;
	char			*save;
}	t_save;

t_save	*gnl_lstnew(int fd);
t_list	*gnl_addback(t_list **lst, int fd);
void	gnl_lstfree(t_list **first, int fd);

#endif
