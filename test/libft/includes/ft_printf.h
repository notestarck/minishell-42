/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:22:48 by estarck           #+#    #+#             */
/*   Updated: 2022/03/15 19:01:07 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_printhexa(unsigned int n, const char *format);
int		ft_ptrhexa(unsigned long long ptr);
char	*ft_uitoa(unsigned int n);
int		ft_uputnbr_pf(unsigned int n, int fd);
int		ft_putnbr_pf(int n, int fd);
int		ft_putstr_pf(char *s, int fd);
int		ft_putchar_pf(char c, int fd);

#endif