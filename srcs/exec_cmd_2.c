/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estarck <estarck@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:14:15 by estarck           #+#    #+#             */
/*   Updated: 2022/07/01 14:19:15 by estarck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**t_arg_to_char(t_arg **cmd)
{
	char	**new;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	new = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd[i])
	{
		new[i] = cmd[i]->str;
		i++;
	}
	new[i] = NULL;
	return (new);
}
