/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:49:59 by estarck           #+#    #+#             */
/*   Updated: 2022/06/03 10:56:31 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char	*err_mess, t_shell *shell, int free_lvl)
{
	if (err_mess != NULL)
		perror(err_mess);
	if (free_lvl == 1)
		free(shell);
}