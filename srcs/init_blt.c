/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:11:05 by estarck           #+#    #+#             */
/*   Updated: 2022/06/30 18:28:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_blt(t_data *shell, t_lst *cmd)
{
	int	i;

	i = 0;
	while (shell->builtins[i])
	{
		if (!(ft_memcmp(shell->builtins[i], cmd->argv[0]->str,
					ft_strlen(shell->builtins[i]))))
		{
			cmd->built = i;
			return (i);
		}
		i++;
	}
	return (-1);
}
