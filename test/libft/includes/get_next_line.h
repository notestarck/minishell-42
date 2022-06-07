/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:51:15 by estarck           #+#    #+#             */
/*   Updated: 2022/04/07 20:06:47 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 42

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char const *s1, char const *s2);

char	*get_next_line(int fd);
char	*ft_read(int fd, char *buf, char *tmp, char *save);
int		ft_checksave(char *save);
char	*ft_savecpy(char *save);
char	*ft_saverest(char *str);

#endif