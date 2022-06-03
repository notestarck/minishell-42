/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:15:52 by estarck           #+#    #+#             */
/*   Updated: 2022/03/10 09:30:28 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *tmp, char *save)
{
	int		s;

	s = 1;
	while (s != 0)
	{
		s = read(fd, buf, BUFFER_SIZE);
		if (s == -1)
		{
			free(buf);
			return (0x0);
		}
		buf[s] = '\0';
		tmp = save;
		if (!tmp)
		{
			tmp = malloc(sizeof(char) * 1);
			tmp[0] = '\0';
		}
		save = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_checksave(save) == 1)
			break ;
	}
	free (buf);
	return (save);
}

int	ft_checksave(char *save)
{
	if (!save)
		return (0);
	while (*save)
	{
		if (*save == '\n')
			return (1);
		save++;
	}
	return (0);
}

char	*ft_savecpy(char *save)
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
	dst = malloc(sizeof(char) * i + 2);
	if (dst == 0x0)
		return (0x0);
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

char	*ft_saverest(char	*save)
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
	tmp = malloc(sizeof(char) * (ft_strlen(save) - i));
	if (tmp == 0x0)
		return (0x0);
	i++;
	while (save[i] != '\0')
		tmp[j++] = save[i++];
	tmp[j] = '\0';
	free(save);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*str;
	char		*buf;
	char		*tmp;

	tmp = 0x0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0x0);
	buf = malloc(BUFFER_SIZE + 1);
	save = ft_read(fd, buf, tmp, save);
	if (save == 0x0)
		return (0x0);
	str = ft_savecpy(save);
	save = ft_saverest(save);
	return (str);
}
