/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:25:42 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/17 22:53:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_gnl.h"

#define BUFFER_SIZE 10

static char	*get_line(char *save)
{
	char	*dst;
	int		i;

	i = 0;
	if (save == 0x0)
		return (0x0);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[0] == '\0')
		return (0x0);
	dst = ft_malloc(sizeof(char) * i + 2);
	i = 0;
	while (save[i] != '\n' && save[i])
	{
		dst[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

static char	*save_remaining(char	*save)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (save == 0x0)
		return (0x0);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\0')
	{
		free (save);
		return (0x0);
	}
	tmp = ft_malloc(sizeof(char) * (ft_strlen(save) - i));
	i++;
	while (save[i] != '\0')
		tmp[j++] = save[i++];
	tmp[j] = '\0';
	free(save);
	return (tmp);
}

static t_list	*get_save(t_list **save_list, int fd)
{
	t_list	*current;

	if (!(*save_list))
	{
		(*save_list) = ft_malloc(sizeof(t_list));
		(*save_list)->content = gnl_lstnew(fd);
		(*save_list)->next = NULL;
	}
	current = *save_list;
	while (current)
	{
		if (((t_save *)(current->content))->fd == fd)
			break ;
		current = current->next;
	}
	if (!current)
		current = gnl_addback(save_list, fd);
	return (current);
}

static int	gnl_read(char *buffer, t_list *current, t_list **save_list, int fd)
{
	int		read_result;
	char	*tmp;

	if (!buffer)
		return (-2);
	read_result = read(fd, buffer, BUFFER_SIZE);
	if (read_result == -1 || !((t_save *)(current->content))->save)
	{
		free(buffer);
		gnl_lstfree(save_list, fd);
		return (-2);
	}
	buffer[read_result] = '\0';
	tmp = ((t_save *)(current->content))->save;
	((t_save *)(current->content))->save = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	return (read_result);
}

char	*ft_gnl(int fd)
{
	static t_list	*save_list;
	t_list			*current;
	char			*buffer;
	char			*tmp;
	int				read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = get_save(&save_list, fd);
	read_result = 1;
	while (read_result != 0)
	{
		buffer = ft_malloc(BUFFER_SIZE * sizeof(char));
		read_result = gnl_read(buffer, current, &save_list, fd);
		if (read_result == -2)
			return (NULL);
		if (ft_strchr(((t_save *)(current->content))->save, (int) '\n'))
			break ;
	}
	tmp = get_line(((t_save *)(current->content))->save);
	((t_save *)(current->content))->save = save_remaining(
			((t_save *)(current->content))->save);
	if (!tmp)
		gnl_lstfree(&save_list, fd);
	return (tmp);
}
